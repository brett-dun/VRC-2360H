
task mobileGoalOut() {
	setSpeedImmediate(leftMobileGoal, 127);
	setSpeedImmediate(rightMobileGoal, 127);
	delay(2000);
	setSpeedImmediate(leftMobileGoal, 0);
	setSpeedImmediate(rightMobileGoal, 0);
}

task autoTask1() {
	setDRFBAngle(-20);
	delay(500); //try to reduce this
	setMGLAngle(120);
}

task autoTask3() {

	delay(500);

	//drop third cone
	setDRFBAngle(-30);
	delay(750);
	setSpeedImmediate(intake, -127);
	//delay(200);
	setDRFBAngle(-10);
	delay(250);
	setSpeedImmediate(intake, 0);

}

task autoTask4() {
	driveInches(9);
}

void getMobileGoal() {

	startTask( pidTask );

	//This is the same as the 20 point autonomous but faster
	startTask( autoTask1 ); //Task: raise DRFB, MGL out
	delay(750); //try to shorten this
	driveInches(31, true); //drive forward
	delay(600); //try to shorten this
	setMGLAngle(0);

}

void auto1(bool twoCones = false) {

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

	if(twoCones) {
		startTask(autoTask3);
	} else {
		//drop second cone
		setDRFBAngle(-35);
		delay(750);
		setSpeedImmediate(intake, -127);
		//delay(200);
		setDRFBAngle(-20);
		delay(250);
		setSpeedImmediate(intake, 0);

		//pick up third cone
		setCBAngle(0);
		delay(400);
		//setDRFBAngle(-30);
		driveInches(8);
		setDRFBAngle(-42);
		setSpeedImmediate(intake, 127);
		delay(750);
		setSpeedImmediate(intake, 0);
		setDRFBAngle(-10);
		setCBAngle(90);

		startTask( autoTask3 );
	}

}
