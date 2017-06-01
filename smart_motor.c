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
	//tSensors sPort; //encoder port - probably not needed
	//tSensors statusLED; //LED used to notify robot status - not yet implemented
	short type; //type of motor
	//short statusLEDenabled; - not yet implemented
	short isPowerExpanderMotor;
	//tMotor slaves[5]; //motors that follow its masters settings - not yet implemented

	int slewRate; //rate at which motors speed is allowed to change per 20 ms

	int currentDraw;
	short status;

	int targetSpeed; //speed to target
	int currentSpeed; //speed that the motor is currently set at

	short encoderType;
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
//Go ahead and use:
void init(); //Run at first to enable other functions
void setEncoderRatio(tMotor name, float ratio); //ratio = Out / In
void setPowerExpander(tMotor one, tMotor two, tMotor three, tMotor four); //Set motors to be in the power expander
void setSlewRate(tMotor name, int slewRate); //Set the rate of motor speed change per 20 ms
void setSpeed(tMotor name, int speed, bool immediate = false); //Use this instead of motor[port1] = 0;
void killAll(); //Stops all motors immediately
/****************************************************/



SmartMotor * getPointer(tMotor name) {
	SmartMotor * pointer = NULL;
	for(int i = 0; i < 10; i++) {
		if(motors[i].mPort == name)
			pointer = &motors[i];
	}
	return pointer;
}

task adjustSpeed() {
	while(true) {
		for(int i = 0; i < 10; i++) {
			SmartMotor * target = &motors[i];
			int speedTarget = target->targetSpeed;
			int speedCurrent = target->currentSpeed;
			if(speedTarget > speedCurrent) {
				if(abs(speedTarget - speedCurrent) > target->slewRate) {
					target->currentSpeed -= 10;
					motor[target->mPort] = target->currentSpeed;
				} else {
					motor[target->mPort] = target->targetSpeed;
					target->currentSpeed = target->targetSpeed;
				}
			} else if(speedTarget < speedCurrent) {
				if(abs(speedTarget - speedCurrent) > motors[i].slewRate) {
					target->currentSpeed += 10;
					motor[target->mPort] = target->currentSpeed;
				} else {
					motor[target->mPort] = target->targetSpeed;
					target->currentSpeed = target->targetSpeed;
				}
			}
		}
		delay(20);
	}
}

task calculateRPM() {
	const short TIME_DELAY = 20;
	while(true) {
		for(int i = 0; i < 10; i++) {
			SmartMotor * target = &motors[i];
			int val = nMotorEncoder[target->mPort];
			int tick = val - target->previousVal;
			target->previousVal = val;

			if(target->encoderType == 1) {
				switch(target->type) {
					case NORMAL: target->rpm = (1000.0 / TIME_DELAY) * (tick/627.2) * 60.0; break;
					case HIGH_SPEED: target->rpm = (1000.0 / TIME_DELAY) * (tick/392.0) * 60.0; break;
					case TURBO_SPEED: target->rpm = (1000.0 / TIME_DELAY) * (tick/261.333) * 60.0; break;
				}
			} else if(target->encoderType == 2) {
				target->rpm = (1000.0 / TIME_DELAY) * (tick/360.0) * 60.0; break;
			}
		}
		calculateCurrentDraw();
		delay(TIME_DELAY);
	}
}

void calculateCurrentDraw() {
	//This may work better in the future: https://www.vexforum.com/index.php/7955-estimating-motor-current/0
	totalCurrent[0] = 0;
	totalCurrent[1] = 0;
	totalCurrent[2] = 0;
	for(int i = 0; i < 10; i++) {
		SmartMotor * target = &motors[i];
		if(abs(target->currentSpeed) > 8) {
			switch(target->type) {
				case NORMAL: target->currentDraw = STALL_CURRENT - ( STALL_CURRENT * target->rpm / (48*log10(abs(target->currentSpeed)-8)) ) * abs(target->currentSpeed / 127.0 );
				case HIGH_SPEED: target->currentDraw = STALL_CURRENT - ( STALL_CURRENT * target->rpm / (76*log10(abs(target->currentSpeed)-8)) ) * abs(target->currentSpeed / 127.0 );
				case TURBO_SPEED: target->currentDraw = STALL_CURRENT - ( STALL_CURRENT * target->rpm / (116*log10(abs(target->currentSpeed)-8)) ) * abs(target->currentSpeed / 127.0 );
			}
		} else {
			target->currentDraw = 0;
		}
		motors[i].status = motors[i].currentDraw > 1.1 ? 1 : 0;
		if(!target->isPowerExpanderMotor && i < 5) {
			totalCurrent[0] += target->currentDraw;
		} else if(!motors[i].isPowerExpanderMotor && i < 5) {
			totalCurrent[1] += target->currentDraw;
		} else {
			totalCurrent[2] += target->currentDraw;
		}
	}
}



void init() {
	if(!isInitialized) {
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
			switch(SensorType(motors[i].mPort)) {
				case I2C_1:
				case I2C_2:
				case I2C_3:
				case I2C_4:
				case I2C_5:
				case I2C_6:
				case I2C_7:
				case I2C_8: motors[i].encoderType = 1; break;
				case dgtl1:
				case dgtl2:
				case dgtl3:
				case dgtl4:
				case dgtl5:
				case dgtl6:
				case dgtl7:
				case dgtl8:
				case dgtl9:
				case dgtl10:
				case dgtl11:
				case dgtl12: motors[i].encoderType = 2; break;
				default: motors[i].encoderType = 0; break;
			}
			motors[i].encoderRatio = 1.0;
			motors[i].slewRate = 10;
		}
		startTask(adjustSpeed);
		startTask(calculateRPM);
		isInitialized = 1;
	}
}

void setEncoderRatio(tMotor name, float ratio) {
	getPointer(name)->encoderRatio = ratio;
}

void setPowerExpander(tMotor one, tMotor two, tMotor three, tMotor four) {
	if(one) getPointer(one)->isPowerExpanderMotor = 1;
	if(two) getPointer(two)->isPowerExpanderMotor = 1;
	if(three) getPointer(three)->isPowerExpanderMotor = 1;
	if(four) getPointer(four)->isPowerExpanderMotor = 1;
}

void setSlewRate(tMotor name, int slewRate) {
	getPointer(name)->slewRate = slewRate;
}

void setSpeed(tMotor name, int speed, bool immediate) {
	speed = speed > 127 ? 127 : speed < -127 ? -127 : speed;
	SmartMotor * target = getPointer(name);
	target->targetSpeed = speed;
	if(immediate) {
		motor[target->mPort] = speed;
		target->currentSpeed = speed;
	}
}

void killAll() {
	for(int i = 0; i < 10; i++) {
		motors[i].targetSpeed = 0;
		motor[motors[i].mPort] = 0;
		motors[i].currentSpeed = 0;
	}
}
