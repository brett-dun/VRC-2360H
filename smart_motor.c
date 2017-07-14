/*
Copyright 2017 Brett Duncan
*/
#pragma systemFile //This prevents "Unreference variable" and "Unreferenced function" warnings


enum MotorType {
	normal, highSpeed, turbo
};


typedef struct {

	MotorType type;

	int targetSpeed;
	int slewRate;

	int slaves[5];
	bool powerExpander;

	int prevEncoderVal;
	float velocity;

	//To Implement:
	float encoderRatio;
	float currentDraw;

} SmartMotor;



/****************************************************/
//These are hidden from the end user
static SmartMotor motors[10];
static float totalCurrent[3];
static tMotor getMotor(int index); //returns the motor at the given index
static ubyte getIndex(tMotor m); //returns the index of a given motor
static task adjustSpeed(); //adjusts the speed of the motors using the slew rate
static task calculateVelocity(); //calculates the velocity of the motors in RPM
//To-Do
//static void calculateCurrentDraw();
/****************************************************/


/****************************************************/
//Go ahead and use:
void init(); //Run at first to enable other functions

void addSlave(tMotor master, tMotor slave); //Run this after init but before other functions
void setEncoderRatio(tMotor m, float ratio); //ratio = Out / In
void setPowerExpander(tMotor motor1, tMotor motor2 = motor1, tMotor motor3 = motor1, tMotor motor4 = motor1); //Set motors to be in the power expander
void setSlewRate(tMotor m, int rate); //Set the rate of motor speed change per 20 ms

void setSpeed(tMotor m, int speed, bool immediate = false); //Use this instead of motor[port1] = 0;
void killAll(); //Stops all motors immediately
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


static task calculateVelocity() {

	const float TIME_DELAY = 50.;

	while(true) {
		for(int i = 0; i < 10; i++) {

			tMotor m = getMotor(i);

			int val = nMotorEncoder[m];
			int ticks = abs(val - motors[i].prevEncoderVal);
			motors[i].prevEncoderVal = val;

			if(getMotorVelocity(motor[m]) >= 0) {

				switch(motors[i].type) {
					case normal: motors[i].velocity = (1000.0 / TIME_DELAY) * (ticks/627.2) * 60.0; break;
					case highSpeed: motors[i].velocity = (1000.0 / TIME_DELAY) * (ticks/392.0) * 60.0; break;
					case turbo: motors[i].velocity = (1000.0 / TIME_DELAY) * (ticks/261.333) * 60.0; break;
				}

			} else
				motors[i].velocity = (1000.0 / TIME_DELAY) * (ticks/360.0) * 60.0; break;

		}


		//calculateCurrentDraw();
		delay(TIME_DELAY);


	}
}


void init() {

	for(int i = 0; i < 10; i++) {

		motors[i].slewRate = 10;
		for(int j = 0; j < 5; j++)
			motors[i].slaves[j] = -1;

		switch(motorType[motor[getMotor(i)]]) {
				case tmotorVex393_HBridge:
				case tmotorVex393_MC29: motors[i].type = normal; break;
				case tmotorVex393HighSpeed_HBridge:
				case tmotorVex393TurboSpeed_HBridge: motors[i].type = highSpeed; break;
				case tmotorVex393HighSpeed_MC29:
				case tmotorVex393TurboSpeed_MC29: motors[i].type = turbo; break;
			}
	}

	startTask(adjustSpeed);
	startTask(calculateVelocity);
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


void setEncoderRatio(tMotor m, float ratio) {
	motors[getIndex(m)].encoderRatio = ratio;
	for(int i = 0; i < 5; i++) {
		if(motors[m].slaves[i] != -1)
			setSlewRate(getMotor(motors[m].slaves[i]), ratio);
	}
}


void setPowerExpander(tMotor motor1, tMotor motor2, tMotor motor3, tMotor motor4) {
	motors[getIndex(motor1)].powerExpander = true;
	motors[getIndex(motor2)].powerExpander = true;
	motors[getIndex(motor3)].powerExpander = true;
	motors[getIndex(motor4)].powerExpander = true;
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
