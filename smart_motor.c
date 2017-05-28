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
	tSensors sPort; //encoder port
	tSensors statusLED; //LED used to notify robot status
	short type; //type of motor
	short statusLEDenabled;
	short isPowerExpanderMotor;

	int slewRate; //rate at which motors speed is allowed to change per 20 ms

	int currentDraw;
	short status;

	int targetSpeed; //speed to target
	int currentSpeed; //speed that the motor is currently set at

	short encoderType;
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
void init(); //Run at begining
void setEncoder(tMotor name, short type, tSensors sensor);
void setPowerExpander(tMotor one, tMotor two, tMotor three, tMotor four);
void setSlewRate(tMotor name, int slewRate);
void setSpeed(tMotor name, int speed); //Try to use this
void setSpeedOverride(tMotor name, int speed); //This is dangerous to use as it works immediately, be careful
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
			int target = motors[i].targetSpeed;
			int current = motors[i].currentSpeed;
			if(target > current) {
				if(abs(target - current) > motors[i].slewRate) {
					motors[i].currentSpeed -= 10;
					motor[motors[i].mPort] = motors[i].currentSpeed;
				} else {
					motor[motors[i].mPort] = motors[i].targetSpeed;
					motors[i].currentSpeed = motors[i].targetSpeed;
				}
			} else if(target < current) {
				if(abs(target - current) > motors[i].slewRate) {
					motors[i].currentSpeed += 10;
					motor[motors[i].mPort] = motors[i].currentSpeed;
				} else {
					motor[motors[i].mPort] = motors[i].targetSpeed;
					motors[i].currentSpeed = motors[i].targetSpeed;
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
			int val = 0;
			if(motors[i].encoderType == 1) {
				val = nMotorEncoder(motors[i].sPort);
			} else if(motors[i].encoderType == 2) {
				val = SensorValue(motors[i].sPort);
			}
			int tick = val - motors[i].previousVal;
			motors[i].previousVal = val;

			if(motors[i].encoderType == 1) {
				switch(motors[i].type) {
					case NORMAL: motors[i].rpm = (1000.0 / TIME_DELAY) * (tick/627.2) * 60.0; break;
					case HIGH_SPEED: motors[i].rpm = (1000.0 / TIME_DELAY) * (tick/392.0) * 60.0; break;
					case TURBO_SPEED: motors[i].rpm = (1000.0 / TIME_DELAY) * (tick/261.333) * 60.0; break;
				}
			} else if(motors[i].encoderType == 2) {
				motors[i].rpm = (1000.0 / TIME_DELAY) * (tick/360.0) * 60.0; break;
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
		if(motors[i].currentSpeed != 0) {
			switch(motors[i].type) {
				case NORMAL: motors[i].currentDraw = STALL_CURRENT + (STALL_CURRENT-FREE_CURRENT)/(0-NORMAL_MAX) * motors[i].rpm;
				case HIGH_SPEED: motors[i].currentDraw = STALL_CURRENT + (STALL_CURRENT-FREE_CURRENT)/(0-HIGH_SPEED_MAX) * motors[i].rpm;
				case TURBO_SPEED: motors[i].currentDraw = STALL_CURRENT + (STALL_CURRENT-FREE_CURRENT)/(0-TURBO_SPEED_MAX) * motors[i].rpm;
			}
		} else
			motors[i].currentDraw = 0;
		if(!motors[i].isPowerExpanderMotor && i < 5) {
			totalCurrent[0] += motors[i].currentDraw;
		} else if(!motors[i].isPowerExpanderMotor && i < 5) {
			totalCurrent[1] += motors[i].currentDraw;
		} else {
			totalCurrent[2] += motors[i].currentDraw;
		}
	}
}



void init() {
	if(!isInitialized) {
		motors[0].mPort = port1; motors[0].sPort = port1;
		motors[1].mPort = port2; motors[1].sPort = port2;
		motors[2].mPort = port3; motors[2].sPort = port3;
		motors[3].mPort = port4; motors[3].sPort = port4;
		motors[4].mPort = port5; motors[4].sPort = port5;
		motors[5].mPort = port6; motors[5].sPort = port6;
		motors[6].mPort = port7; motors[6].sPort = port7;
		motors[7].mPort = port8; motors[7].sPort = port8;
		motors[8].mPort = port9; motors[8].sPort = port9;
		motors[9].mPort = port10; motors[9].sPort = port10;
		for(int i = 0; i < 10; i++) {
			switch(motorType[motors[i].mPort]) {
				case tmotorVex393_HBridge:
				case tmotorVex393_MC29: motors[i].type = NORMAL; break;
				case tmotorVex393HighSpeed_HBridge:
				case tmotorVex393TurboSpeed_HBridge: motors[i].type = HIGH_SPEED; break;
				case tmotorVex393HighSpeed_MC29:
				case tmotorVex393TurboSpeed_MC29: motors[i].type = TURBO_SPEED; break;
			}
			motors[i].slewRate = 10;
		}
		startTask(adjustSpeed);
		startTask(calculateRPM);
		isInitialized = 1;
	}
}

void setEncoder(tMotor name, short type, tSensors sensor) {
	SmartMotor * target = getPointer(name);
	target->encoderType = type;
	target->sPort = sensor;
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

void setSpeed(tMotor name, int speed) {
	speed = speed > 127 ? 127 : speed;
	speed = speed < -127 ? -127 : speed;
	getPointer(name)->targetSpeed = speed;
}

void setSpeedOverride(tMotor name, int speed) {
	speed = speed > 127 ? 127 : speed;
	speed = speed < -127 ? -127 : speed;
	SmartMotor * target = getPointer(name);
	target->targetSpeed = speed;
	motor[target->mPort] = speed;
	target->currentSpeed = speed;
}

void killAll() {
	for(int i = 0; i < 10; i++) {
		motors[i].targetSpeed = 0;
		motor[motors[i].mPort] = 0;
		motors[i].currentSpeed = 0;
	}
}
