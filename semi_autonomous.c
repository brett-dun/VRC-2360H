
task aTask() {

	disableDRFBPID();

	setSpeed(rightDRFB, 127, true);
	while( SensorValue[ultrasonic] < 5)
		delay(20);
	setSpeed(rightDRFB, 0, true);

	setCBAngle(90); //raise drfb
	delay(750); //wait for chain bar to finish moving
	intakeCone(500, true); //release the cone
}


task bTask() {

	stopTask(aTask);

	setCBAngle(0);
	delay(750);
	setDRFBAngle(-30);
	setSpeed(intake, 127, true);

	while( getMotorVelocity(intake) != 0 )
		delay(20);
	setSpeed(intake, 0, true);
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
