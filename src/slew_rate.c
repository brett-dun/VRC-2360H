#include "slew_rate.h"



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



void init() {

	for(int i = 0; i < 10; i++) {

		motors[i].targetSpeed = 0;
		motors[i].currentSpeed = 0;
		motors[i].slewRate = 10;
		motors[i].reversed = false;

		for(int j = 0; j < 5; j++)
			motors[i].slaves[j] = -1;

	}

	adjustSpeedTask = taskRunLoop(adjustSpeed, 20);

}



void enable() {
	taskDelete(adjustSpeedTask); //Make sure this task is stopped
	adjustSpeedTask = taskRunLoop(adjustSpeed, 20); //Run this task again
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



void setSlewRate(int motor, unsigned int rate) {
	motors[motor].slewRate = rate;
	for(int i = 0; i < 5; i++) {
		if(motors[motor].slaves[i] != -1)
			setSlewRate(motors[motor].slaves[i], rate);
	}
}



void setSpeed(int motor, int speed, bool immediate) {
	speed = speed > 127 ? 127 : (speed < -127 ? -127 : speed);
	speed = motors[motor].reversed ? -speed : speed;
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
