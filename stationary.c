
void returnMobileGoal() {

	driveInches(-20);

	if(leftStart)
		turnDegrees(180);
	else
		turnDegrees(-180);

	/*driveInches(3);

	if(leftStart)
		turnDegrees(90);
	else
		turnDegrees(-90);*/

	driveInches(20);
	startTask( mobileGoalOut );
	delay(2000);

	driveInches(-20);

}


void auto2() {

	startTask(pidTask);

	setDRFBAngle(15);
	driveInches(14);
	setCBAngle(0);

	delay(500);

	setSpeedImmediate(intake, -127);
	delay(250);
	setDRFBAngle(25);
	delay(100);
	setSpeedImmediate(intake, 0);

	driveInches(-18);

	//check these angles
	if(leftStart)
		turnDegrees(-105);
	else
		turnDegrees(105);

	getMobileGoal();
	delay(950); //check this

	//drop first cone
	setDRFBAngle(-40);
	setSpeedImmediate(intake, -127);
	//delay(200);
	setDRFBAngle(-20);
	delay(250);
	setSpeedImmediate(intake, 0);

	//pick up second cone
	setCBAngle(0);
	delay(400);
	//setDRFBAngle(-30);
	//startTask(autoTask4);
	driveInches(8);
	setDRFBAngle(-42);
	setSpeedImmediate(intake, 127);
	delay(750);
	setSpeedImmediate(intake, 0);
	setDRFBAngle( -15 );
	setCBAngle(90);
	delay(500);

	startTask(autoTask3);

	driveInches(-30);

	if(leftStart)
		turnDegrees(205);
	else
		turnDegrees(-205);

	setMGLAngle(120);
	delay(750);

	driveInches(-20);
	setMGLAngle(70);

}
