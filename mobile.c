
task mobileGoalOut() {
	setSpeedImmediate(leftMobileGoal, 127);
	setSpeedImmediate(rightMobileGoal, 127);
	delay(2000);
	setSpeedImmediate(leftMobileGoal, 0);
	setSpeedImmediate(rightMobileGoal, 0);
}

task mobileGoalIn() {
	setSpeedImmediate(leftMobileGoal, -127);
	setSpeedImmediate(rightMobileGoal, -127);
	delay(2000);
	setSpeedImmediate(leftMobileGoal, 0);
	setSpeedImmediate(rightMobileGoal, 0);
}

task autoTask1() {
	setDRFBAngle(-35);
	delay(500); //try to reduce this
	startTask( mobileGoalOut );
}

task autoTask2() {
	releaseCone(2000);
}

task autoTask3() {
	delay(250);
	setCBAngle(90);
	delay(750);
	releaseCone(2000);
}

void getMobileGoal() {

	startTask( pidTask );

	//This is the same as the 20 point autonomous but faster
	startTask( autoTask1 ); //Task: raise DRFB, MGL out
	delay(1000); //try to shorten this
	driveInches( 40 ); //drive forward
	delay(500); //try to shorten this
	startTask( mobileGoalIn ); //Task: MGL in

}

void auto1() {

	getMobileGoal();
	delay(2000); //check this
	releaseCone( 550 );

	//start working on code here
	setCBAngle( 0 );
	delay(500);
	setSpeedImmediate(intake, -127);
	setDRFBAngle( -50 );
	delay(1000);
	setSpeedImmediate(intake, 0); //intake cone
	setDRFBAngle( -25 );
	delay(250);
	startTask( autoTask3 );

}
