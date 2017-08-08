/*static void adjustSpeed() {
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


static void calculateVelocity() {

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

	//startTask(adjustSpeed);
	//startTask(calculateVelocity);
}

void enable() {
	//stopTask(adjustSpeed);
	//stopTask(calculateVelocity);

	//startTask(adjustSpeed);
	//startTask(calculateVelocity);
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
}*/
