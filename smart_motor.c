/*
Copyright 2017 Brett Duncan
*/
#pragma systemFile

#define NORMAL 0
#define HIGH_SPEED 1
#define TURBO_SPEED 2

#define INTERNAL 1
#define EXTERNAL 2

#define NORMAL_MAX 100
#define HIGH_SPEED_MAX 160
#define TURBO_SPEED_MAX 240

#define FREE_CURRENT 0.37
#define STALL_CURRENT 4.8

typedef struct {

	tMotor mPort; //motor port
	tSensors sPort; //encoder port - probably not needed
	//tSensors statusLED; //LED used to notify robot status - not yet implemented
	ubyte type; //type of motor
	//short statusLEDenabled; - not yet implemented
	ubyte isPowerExpanderMotor;
	tMotor slaves[5]; //motors that follow its master's settings, a motor may have a maximum of five slaves, slaves may not have slaves

	int slewRate; //rate at which motors speed is allowed to change per 20 ms

	float currentDraw;
	ubyte status;

	int targetSpeed; //speed to target
	int currentSpeed; //speed that the motor is currently set at

	ubyte encoderType;
	float encoderRatio;
	int previousVal;
	float rpm;

} SmartMotor;


/****************************************************/
//Don't touch:
static short isInitialized = 0;
static SmartMotor motors[10];
static float totalCurrent[3];
SmartMotor * getPointer(tMotor name);
task adjustSpeed();
task calculateRPM();
void calculateCurrentDraw(); //work on this function
/****************************************************/


/****************************************************/
//Go ahead and use:
void init(); //Run at first to enable other functions

void addSlave(tMotor master, tMotor slave, short slot); //Run this after init but before other functions
void setExternalEncoder(tMotor name, tSensors port, float ratio); //ratio = Out / In
void setPowerExpander(tMotor one, tMotor two = one, tMotor three = one, tMotor four = one); //Set motors to be in the power expander
void setSlewRate(tMotor name, int slewRate); //Set the rate of motor speed change per 20 ms

void setSpeed(tMotor name, int speed, bool immediate = false); //Use this instead of motor[port1] = 0;
int getCurrentSpeed(tMotor name);
float getRPM(tMotor name);
void killAll(); //Stops all motors immediately
/****************************************************/


//Done
SmartMotor * getPointer(tMotor name) {
	/*SmartMotor * pointer = NULL;
	for(int i = 0; i < 10; i++) {
		if(motors[i].mPort == name)
			pointer = &motors[i];
	}
	return pointer;*/
	switch(name) {
		case port1: return &motors[0];
		case port2: return &motors[1];
		case port3: return &motors[2];
		case port4: return &motors[3];
		case port5: return &motors[4];
		case port6: return &motors[5];
		case port7: return &motors[6];
		case port8: return &motors[7];
		case port9: return &motors[8];
		case port10: return &motors[9];
		default: return NULL;
	}
}

//Done
task adjustSpeed() {
	while(true) {
		for(int i = 0; i < 10; i++) {
			SmartMotor * target = &motors[i];
			int speedTarget = target->targetSpeed;
			int speedCurrent = target->currentSpeed;
			if(speedTarget != speedCurrent) {
				if(abs(speedTarget - speedCurrent) > target->slewRate) {
					target->currentSpeed += speedCurrent < speedTarget ? target->slewRate : -(target->slewRate);
					motor[target->mPort] = target->currentSpeed;
				} else {
					motor[target->mPort] = speedTarget;
					target->currentSpeed = speedTarget;
				}
			}
		}
		delay(20);
	}
}

//Check results
task calculateRPM() {
	const float TIME_DELAY = 50.;

	while(true) {
		for(int i = 0; i < 10; i++) {

			int val = motors[i].encoderType ? SensorValue(motors[i].sPort) : nMotorEncoder[motors[i].mPort];
			int tick = abs(val - motors[i].previousVal);
			motors[i].previousVal = val;

			if(motors[i].encoderType == 0) {
				switch(motors[i].type) {
					case NORMAL: motors[i].rpm = (1000.0 / TIME_DELAY) * (tick/627.2) * 60.0; break;
					case HIGH_SPEED: motors[i].rpm = (1000.0 / TIME_DELAY) * (tick/392.0) * 60.0; break;
					case TURBO_SPEED: motors[i].rpm = (1000.0 / TIME_DELAY) * (tick/261.333) * 60.0; break;
				}
			} else {
				motors[i].rpm = (1000.0 / TIME_DELAY) * (tick/360.0) * 60.0; break;
			}
		}
		calculateCurrentDraw();
		delay(TIME_DELAY);
	}
}

//Not working
void calculateCurrentDraw() {

	const ubyte expectedSpeed[128] = {
		0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  5,  9, 13, 17, 20, 24,
		27, 30, 33, 36, 39, 42, 44, 47, 49, 52, 54, 56, 59, 61, 63, 64,
		66, 68, 70, 71, 73, 74, 76, 77, 79, 80, 81, 82, 83, 84, 85, 86,
		87, 88, 89, 90, 91, 92, 92, 93, 94, 94, 95, 95, 96, 96, 97, 97,
		98, 98, 99, 99, 99,100,100,100,101,101,101,102,102,102,103,103,
		103,103,104,104,104,104,105,105,105,105,105,106,106,106,106,107,
		107,107,107,108,108,108,108,108,109,109,109,109,110,110,110,110,
		111,111,111,111,111,112,112,112,112,112,113,113,113,113,113,114
	};

	//Calculation source: https://www.vexforum.com/index.php/7955-estimating-motor-current/0
	totalCurrent[0] = 0;
	totalCurrent[1] = 0;
	totalCurrent[2] = 0;

	for(int i = 0; i < 10; i++) {

		int speed = abs(motors[i].currentSpeed);
		if(expectedSpeed[speed] != 0) {

			float driveVoltage = (motors[i].currentSpeed / 127.0) * (nAvgBatteryLevel / 1000.);
			float bemfVoltage = 0.0;

			switch(motors[i].type) {
				case NORMAL: bemfVoltage = motors[i].rpm / expectedSpeed[abs(motors[i].currentSpeed)] * driveVoltage; break;
				case HIGH_SPEED: bemfVoltage = (motors[i].rpm / 1.6) / expectedSpeed[abs(motors[i].currentSpeed)] * driveVoltage; break;
				case TURBO_SPEED: bemfVoltage = (motors[i].rpm / 2.4) / expectedSpeed[abs(motors[i].currentSpeed)] * driveVoltage; break;
			}

			motors[i].currentDraw = driveVoltage - bemfVoltage;// > 0.0 ? driveVoltage - bemfVoltage : 0.0;
		} else {
			motors[i].currentDraw = 0.0;
		}

		/*motors[i].status = motors[i].currentDraw > 1.1 ? 1 : 0;

		if(motors[i].isPowerExpanderMotor) {
			totalCurrent[2] += motors[i].currentDraw;
		} else if(i < 5) {
			totalCurrent[1] += motors[i].currentDraw;
		} else {
			totalCurrent[0] += motors[i].currentDraw;
		}*/
	}
}


//Done
void init() {
	if((isInitialized ^ 1)) {
		motors[0].mPort = port1;// motors[0].sPort = port1;
		motors[1].mPort = port2;// motors[1].sPort = port2;
		motors[2].mPort = port3;// motors[2].sPort = port3;
		motors[3].mPort = port4;// motors[3].sPort = port4;
		motors[4].mPort = port5;// motors[4].sPort = port5;
		motors[5].mPort = port6;// motors[5].sPort = port6;
		motors[6].mPort = port7;// motors[6].sPort = port7;
		motors[7].mPort = port8;// motors[7].sPort = port8;
		motors[8].mPort = port9;// motors[8].sPort = port9;
		motors[9].mPort = port10;// motors[9].sPort = port10;
		for(int i = 0; i < 10; i++) {
			switch(motorType[motors[i].mPort]) {
				case tmotorVex393_HBridge:
				case tmotorVex393_MC29: motors[i].type = NORMAL; break;
				case tmotorVex393HighSpeed_HBridge:
				case tmotorVex393TurboSpeed_HBridge: motors[i].type = HIGH_SPEED; break;
				case tmotorVex393HighSpeed_MC29:
				case tmotorVex393TurboSpeed_MC29: motors[i].type = TURBO_SPEED; break;
			}
			motors[i].encoderRatio = 1.0;
			motors[i].slewRate = 10;
		}
		startTask(adjustSpeed);
		startTask(calculateRPM);
		isInitialized = 1;
	}
}

//Needs improvement
void addSlave(tMotor master, tMotor slave, short slot) {
	getPointer(master)->slaves[slot] = slave;
}

//Done
void setExternalEncoder(tMotor name, tSensors port, float ratio) {
	SmartMotor * target = getPointer(name);
	target->sPort = port;
	target->encoderType = 1;
	target->encoderRatio = ratio;
	for(int i = 0; i < 5; i++) {
		SmartMotor * slave = getPointer(target->slaves[i]);
		if(slave) {
			slave->sPort = port;
			slave->encoderType = 1;
			slave->encoderRatio = ratio;
		}
	}
}

//Done
void setPowerExpander(tMotor one, tMotor two, tMotor three, tMotor four) {
	getPointer(one)->isPowerExpanderMotor = 1;
	getPointer(two)->isPowerExpanderMotor = 1;
	getPointer(three)->isPowerExpanderMotor = 1;
	getPointer(four)->isPowerExpanderMotor = 1;
}

//Done
void setSlewRate(tMotor name, int slewRate) {
	SmartMotor * target = getPointer(name);
	target->slewRate = slewRate;
	for(int i = 0; i < 5; i++) {
		if(&target->slaves[i])
			getPointer(target->slaves[i])->slewRate = slewRate;
	}
}

//Done
void setSpeed(tMotor name, int speed, bool immediate) {
	speed = speed > 127 ? 127 : speed < -127 ? -127 : speed;
	SmartMotor * target = getPointer(name);
	target->targetSpeed = speed;
	for(int i = 0; i < 5; i++) {
		//if(&target->slaves[i])
			getPointer(target->slaves[i])->targetSpeed = speed;
	}
	if(immediate) {
		motor[target->mPort] = speed;
		target->currentSpeed = speed;
		for(int i = 0; i < 5; i++) {
			//if(&target->slaves[i]) {
				motor[getPointer(target->slaves[i])->mPort] = speed;
				getPointer(target->slaves[i])->currentSpeed = speed;
			//}
		}
	}
}

//Done
float getCurrentSpeed(tMotor name) {
	return getPointer(name)->currentSpeed;
}

//Done
float getRPM(tMotor name) {
	return getPointer(name)->rpm;
}

//Done
void killAll() {
	for(int i = 0; i < 10; i++) {
		motors[i].targetSpeed = 0;
		motor[motors[i].mPort] = 0;
		motors[i].currentSpeed = 0;
	}
}
