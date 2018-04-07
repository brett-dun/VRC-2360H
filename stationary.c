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

	if(leftStart)
		turnDegrees(-105);
	else
		turnDegrees(105);

	//This is the same as the 20 point autonomous but faster
	startTask( autoTask1 ); //Task: raise DRFB, MGL out
	delay(750); //try to shorten this
	driveInches(31, true); //drive forward
	delay(600); //try to shorten this
	setMGLAngle(0);
	delay(950); //check this

	/*//drop first cone
	setDRFBAngle(-40);
	setSpeedImmediate(intake, -127);
	//delay(200);
	setDRFBAngle(-20);
	delay(250);
	setSpeedImmediate(intake, 0);*/
	setDRFBAngle(-20);

	//pick up second cone
	setCBAngle(0);
	delay(400);
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
