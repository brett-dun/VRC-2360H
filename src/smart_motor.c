#include "smart_motor.h"

static void adjustSpeed() {
	//while(true) {
		for(int i = 0; i < 10; i++) {
			if(motors[i].currentSpeed != motors[i].targetSpeed) {
				if(abs(motors[i].currentSpeed - motors[i].targetSpeed) > motors[i].slewRate) {
					motors[i].currentSpeed += motors[i].currentSpeed < motors[i].targetSpeed ? motors[i].slewRate : -motors[i].slewRate;
          motorSet(i+1,motors[i].currentSpeed);
        } else {
          motors[i].currentSpeed = motors[i].targetSpeed;
          motorSet(i+1,motors[i].currentSpeed);
        }
			}
		}
		//delay(20);
	//}
}


/*static void calculateVelocity() {

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
*/

void init() {

	for(int i = 0; i < 10; i++) {

		motors[i].slewRate = 10;
		for(int j = 0; j < 5; j++)
			motors[i].slaves[j] = -1;

		/*switch(motorType[motor[getMotor(i)]]) {
				case tmotorVex393_HBridge:
				case tmotorVex393_MC29: motors[i].type = normal; break;
				case tmotorVex393HighSpeed_HBridge:
				case tmotorVex393TurboSpeed_HBridge: motors[i].type = highSpeed; break;
				case tmotorVex393HighSpeed_MC29:
				case tmotorVex393TurboSpeed_MC29: motors[i].type = turbo; break;
			}*/
	}
	adjustSpeedTask = taskRunLoop(adjustSpeed, 20);
	//startTask(calculateVelocity);
}

void enable() {
	//stopTask(adjustSpeed);
	//stopTask(calculateVelocity);

	//startTask(adjustSpeed);
	//startTask(calculateVelocity);
}

void addSlave(int master, int slave) {
  slave = slave < 1 ? 1 : (slave > 10 ? 10 : slave);
	for(int i = 0; i < 5; i++) {
		if(motors[master].slaves[i] == -1) {
			motors[master].slaves[i] = slave;
			return;
		}
	}
}
/*

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

*/
void setSlewRate(int motor, unsigned int rate) {
	motors[motor].slewRate = rate;
	for(int i = 0; i < 5; i++) {
		if(motors[motor].slaves[i] != -1)
			setSlewRate(motors[motor].slaves[i], rate);
	}
}


void setSpeed(int motor, int speed, bool immediate) {
	speed = speed > 127 ? 127 : (speed < -127 ? -127 : speed);
	motors[motor].targetSpeed = speed;
	if(immediate) {
		motors[motor].currentSpeed = speed;
    motorSet(motor+1, motors[motor].currentSpeed);
  }
	for(int i = 0; i < 5; i++) {
		if(motors[motor].slaves[i] != -1)
			setSpeed(motors[motor].slaves[i], speed, immediate);
	}
}


void killAll() {
	for(int i = 0; i < 10; i++) {
		motors[i].targetSpeed = 0;
		motors[i].currentSpeed = 0;
    motorSet(i+1, 0);
	}
}
