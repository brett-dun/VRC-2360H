/*
Copyright 2017-2018 Brett Duncan
Smart Motor
Version 1.4 - MotorType brought back from version 1.0 + custom data types
-- Past Versions --
Version 1.0 - First Release
Version 1.1 - Higher Performance, Reduced Features
Version 1.2 - Cleaned Up Code, Better Ease of Use
Version 1.2.2 - Cleaned Up Code, Better Ease of Use
Version 1.3 - Added "setSpeedImmediate" For Clearity
*/
#pragma systemFile //This prevents "Unreference variable" and "Unreferenced function" warnings

enum MotorType {
	normal, highSpeed, turbo
};

/****************************************************/
//End User Functions
void init(); //Run at first to enable other functions
void enable(); //Turn on at the begining of autonomous and driver control code

void addSlave(tMotor master, tMotor slave); //Run this after init but before other functions
void setSlewRate(tMotor m, int8 rate); //Set the rate of motor speed change per 20 ms

//MotorType getMotorType(tMotor m);

void setSpeed(tMotor m, int16 speed, bool immediate = false); //Use this instead of motor[port1] = 0;
void setSpeedImmediate(tMotor m, int16 speed);
void killAll(); //Stops all motors immediately
/****************************************************/




















/****************************************************/
//The end user does not need worry about anything below this




typedef struct {

	MotorType type;

	int8 targetSpeed;
	int8 slewRate;

	int8 slaves[5];

} SmartMotor;


static SmartMotor motors[10];
static tMotor getMotor(uint8 index); //returns the motor at the given index
static unsigned char getIndex(tMotor m); //returns the index of a given motor
static task adjustSpeed(); //adjusts the speed of the motors using the slew rate


static tMotor getMotor(uint8 index) {
	switch(index) {
		case 0: return port1;
		case 1: return port2;
		case 2: return port3;
		case 3: return port4;
		case 4: return port5;
		case 5: return port6;
		case 6: return port7;
		case 7: return port8;
		case 8: return port9;
		default: return port10;
	}
}


static unsigned char getIndex(tMotor m) {
	switch(m) {
		case port1: return 0;
		case port2: return 1;
		case port3: return 2;
		case port4: return 3;
		case port5: return 4;
		case port6: return 5;
		case port7: return 6;
		case port8: return 7;
		case port9: return 8;
		default: return 9;
	}
}


static task adjustSpeed() {
	while(true) {
		for(int8 i = 0; i < 10; i++) {
			tMotor m = getMotor(i);
			if(motor[m] != motors[i].targetSpeed) {
				if(abs(motor[m] - motors[i].targetSpeed) > motors[i].slewRate)
					motor[m] += motor[m] < motors[i].targetSpeed ? motors[i].slewRate : -motors[i].slewRate;
				else
					motor[m] = motors[i].targetSpeed;
			}
		}
		delay(20);
	}
}


void init() {

	for(int8 i = 0; i < 10; i++) {
		switch(motorType[motor[getMotor(i)]]) {
			case tmotorVex393_HBridge:
			case tmotorVex393_MC29: motors[i].type = normal; break;
			case tmotorVex393HighSpeed_HBridge:
			case tmotorVex393HighSpeed_MC29: motors[i].type = highSpeed; break;
			case tmotorVex393TurboSpeed_HBridge:
			case tmotorVex393TurboSpeed_MC29: motors[i].type = turbo; break;
		}
		motors[i].slewRate = 10;
		for(int8 j = 0; j < 5; j++)
			motors[i].slaves[j] = -1;
	}

	startTask(adjustSpeed);
}

void enable() {
	stopTask(adjustSpeed);
	startTask(adjustSpeed);
}


void addSlave(tMotor master, tMotor slave) {
	ubyte m = getIndex(master);
	for(int8 i = 0; i < 5; i++) {
		if(motors[m].slaves[i] == -1) {
			motors[m].slaves[i] = getIndex(slave);
			return;
		}
	}
}

MotorType getMotorType(tMotor m) {

}


void setSlewRate(tMotor m, int8 rate) {
	rate = abs(rate);
	motors[getIndex(m)].slewRate = rate;
	for(int8 i = 0; i < 5; i++) {
		if(motors[m].slaves[i] != -1)
			setSlewRate(getMotor(motors[m].slaves[i]), rate);
	}
}


void setSpeed(tMotor m, int16 speed, bool immediate) {
	speed = speed > 127 ? 127 : (speed < -127 ? -127 : speed);
	motors[getIndex(m)].targetSpeed = speed;
	if(immediate)
		motor[m] = speed;
	for(int8 i = 0; i < 5; i++) {
		if(motors[m].slaves[i] != -1)
			setSpeed(getMotor(motors[m].slaves[i]), speed, immediate);
	}
}


void setSpeedImmediate(tMotor m, int16 speed) {
	setSpeed(m, speed, true);
}


void killAll() {
	for(int8 i = 0; i < 10; i++) {
		motors[i].targetSpeed = 0;
		motor[getMotor(i)] = 0;
	}
}
