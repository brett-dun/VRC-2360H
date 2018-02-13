
task aTask() {

	disableDRFBPID();

	setSpeedImmediate(rightDRFB, 127);
	while( SensorValue[ultrasonic] < 6)
		delay(20);
	setSpeedImmediate(rightDRFB, 0);

	setCBAngle(90); //raise drfb
	delay(750); //wait for chain bar to finish moving
	releaseCone(500); //release the cone
}


task bTask() {

	setCBAngle(0);

	delay(750);
	setSpeedImmediate(rightDRFB, -127);
	setSpeedImmediate(intake, 127);
	delay(100);

	while( getMotorVelocity(rightDRFB) != 0 || getMotorVelocity(intake) != 0) {
		if(getMotorVelocity(rightDRFB) == 0)
			setSpeedImmediate(rightDRFB, 0);
		if(getMotorVelocity(intake) == 0)
			setSpeedImmediate(intake, 0);
		delay(20);
	}
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

		if( vexRT[Btn7UXmtr2]&&vexRT[Btn7DXmtr2] )
			return;

		delay(20);

	}

}
