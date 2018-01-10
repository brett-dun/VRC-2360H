/*
Copyright 2017 Brett Duncan
Smart Motor
Version 1.2 - Cleaned Up Code, Better Ease of Use
-- Past Versions --
Version 1.0 - First Release
Version 1.1 - Higher Performance, Reduced Features
*/
#pragma systemFile //This prevents "Unreference variable" and "Unreferenced function" warnings


/****************************************************/
//End User Functions
void init(); //Run at first to enable other functions
void enable(); //Tun at the begining of autonomous and driver control code

void addSlave(tMotor master, tMotor slave); //Run this after init but before other functions
void setSlewRate(tMotor m, int rate); //Set the rate of motor speed change per 20 ms

void setSpeed(tMotor m, int speed, bool immediate = false); //Use this instead of motor[port1] = 0;
void killAll(); //Stops all motors immediately
/****************************************************/

typedef struct {

	int targetSpeed;
	int slewRate;
	int slaves[5];

} SmartMotor;

/****************************************************/
//These are hidden from the end user
static SmartMotor motors[10];
static tMotor getMotor(int index); //returns the motor at the given index
static ubyte getIndex(tMotor m); //returns the index of a given motor
static task adjustSpeed(); //adjusts the speed of the motors using the slew rate
/****************************************************/





static tMotor getMotor(int index) {
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

static ubyte getIndex(tMotor m) {
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
		for(int i = 0; i < 10; i++) {
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

	for(int i = 0; i < 10; i++) {

		motors[i].slewRate = 10;
		for(int j = 0; j < 5; j++)
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
	for(int i = 0; i < 5; i++) {
		if(motors[m].slaves[i] == -1) {
			motors[m].slaves[i] = getIndex(slave);
			return;
		}
	}
}

void setSlewRate(tMotor m, int rate) {
	rate = abs(rate);
	motors[getIndex(m)].slewRate = rate;
	for(int i = 0; i < 5; i++) {
		if(motors[m].slaves[i] != -1)
			setSlewRate(getMotor(motors[m].slaves[i]), rate);
	}
}


void setSpeed(tMotor m, int speed, bool immediate) {
	speed = speed > 127 ? 127 : (speed < -127 ? -127 : speed);
	motors[getIndex(m)].targetSpeed = speed;
	if(immediate)
		motor[m] = speed;
	for(int i = 0; i < 5; i++) {
		if(motors[m].slaves[i] != -1)
			setSpeed(getMotor(motors[m].slaves[i]), speed, immediate);
	}
}


void killAll() {
	for(int i = 0; i < 10; i++) {
		motors[i].targetSpeed = 0;
		motor[getMotor(i)] = 0;
	}
}
