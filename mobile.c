
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
	setDRFBAngle(-20);
	delay(500); //try to reduce this
	startTask( mobileGoalOut );
}

task autoTask2() {
	setDRFBAngle(-40);
	delay(500);
	setSpeedImmediate(intake, -127);
	delay(1000);
	setDRFBAngle(-20);
	setSpeedImmediate(intake, 0);
}

task autoTask3() {
	delay(750);
	setCBAngle(90);
	delay(750);
	setDRFBAngle(-35);
	delay(750);

	setSpeedImmediate(intake, -127);
	delay(1000);
	setDRFBAngle(-25);
	delay(1000);
	setSpeedImmediate(intake, 0);
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
	delay(1500); //check this
	driveInches( 2.5 );

	setDRFBAngle(-40);
	delay(500);
	setSpeedImmediate(intake, -127);
	delay(500);
	setDRFBAngle(-20);
	setSpeedImmediate(intake, 0);



	//start working on code here
	setCBAngle( 0 );
	delay(500);
	setSpeedImmediate(intake, 127);
	setDRFBAngle( -55 );
	delay(1250);
	setDRFBAngle( -20 );
	setSpeedImmediate(intake, 0);
	startTask( autoTask3 );

}
