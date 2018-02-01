
task aTask() {

	disableDRFBPID();

	setSpeedImmediate(rightDRFB, 127);
	while( SensorValue[ultrasonic] < 5)
		delay(20);
	setSpeedImmediate(rightDRFB, 0);

	setCBAngle(90); //raise drfb
	delay(750); //wait for chain bar to finish moving
	rleaseCone(500); //release the cone
}


task bTask() {

	stopTask(aTask);

	setCBAngle(0);
	delay(750);
	setDRFBAngle(-30);
	setSpeedImmediate(intake, 127);

	while( getMotorVelocity(intake) != 0 )
		delay(20);
	setSpeedImmediate(intake, 0);
}


void semiAutonomous() {

	while(true) {

		setSpeed(leftDrive, vexRT[Ch3] * 0.35); //Set leftDrive speed
		setSpeed(rightDrive, vexRT[Ch2] * 0.35); //Set rightDrive speed

		if(vexRT[Btn6U]) {
			stopTask(bTask);
			startTask(aTask);
		} else if(vexRT[Btn6D]) {
			stopTask(aTask);
			startTask(bTask);
		}

		if(false)
			return;

		delay(20);

	}

}
