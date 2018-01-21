
void auto2() {

	startTask(pidTask);

	driveInches(6);

	setDRFBAngle(-5);

	setSpeed(chainBar, -127, true);
	delay(1500);
	setSpeed(chainBar, 0, true);

	delay(500);

	driveInches(5);

	intakeCone(1000, true); //Drop cone onto stationary goal

	driveInches(-12);

	/*
	if(leftStart)
		turnDegrees(90);
	else
		turnDegrees(-90);
	*/

	//driveInches(12);

	/*
	if(leftStart)
		turnDegrees(-45);
	else
		turnDegrees(45);
	*/

	//driveInches(45);

	//raiseMobileGoal(); //pickup mobile goal

}
