
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

task skillsTask1() {
	setDRFBAngle(-35);
	delay(500); //try to reduce this
	startTask( mobileGoalOut );
}

task skillsTask2() {
	releaseCone(2000);
}



void skills() {

	startTask( pidTask );

	//This is the same as the 20 point autonomous but faster
	startTask( skillsTask1 ); //Task: raise DRFB, MGL out
	delay( 1000 ); //try to shorten this
	driveInches( 40 ); //drive forward
	delay( 500 ); //try to shorten this
	startTask( mobileGoalIn ); //Task: MGL in
	driveInches( -22 ); //drive backward
	startTask( skillsTask2 );
	turnDegrees( -45 );
	driveInches( -30 ); //drive backward
	turnDegrees( -90 );
	driveInches( 19 ); //drive forward
	//Place mobile goal into 20 point zone
	setSpeedImmediate(leftMobileGoal, 127);
	delay( 1000 ); //let the mobile goal settle - try to shorten this
	driveInches( -13 ); //drive backward
	setSpeed(leftMobileGoal, 0);

	//start working on the code here
	startTask( mobileGoalIn ); //Task: MGL in
	turnDegrees( -90 );
	return; //for testing
	driveInches( 15 ); //drive forward
	turnDegrees( -45 );
	startTask( mobileGoalOut ); //Task: MGL out
	driveInches( 30 ); //drive forward
	startTask( mobileGoalIn ); //Task: MGL in
	//delay(500);
	driveInches( -30 ); //drive backward
	turnDegrees( -180 );
	driveInches( 6 ); //drive forward
	startTask( mobileGoalOut ); //MGL out //Place mobile goal into 10 point zone
	delay( 1500 );

	driveInches( -12 ); //drive backward
	startTask( mobileGoalIn ); //Task: MGL in
	turnDegrees( 90 );
	setDrive( -64 ); //back up against wall
	delay( 2000 );
	setDrive( 0 );
	driveInches( 36 ); //drive forward
	startTask( mobileGoalOut ); //Task: MGL out
	turnDegrees( 45 );
	driveInches( 12 );//drive forward
	startTask( mobileGoalIn ); //Task: MGL in
	delay(500);
	driveInches( -sqrt(2 * 24*24) ); //drive backwards
	turnDegrees( -135 );
	driveInches( 18 ); //drive forward
	startTask( mobileGoalOut ); //MGL out //Place mobile goal into middle of 10 point zone
	turnDegrees( -45 );
	delay( 750 );

	driveInches( -6 ); //drive backward
	startTask( mobileGoalIn ); //Task: MGL in
	turnDegrees( 90 );
	driveInches( sqrt(2 * 12*12) ); //drive forward
	startTask( mobileGoalOut ); //Task: MGL out
	turnDegrees( 90 );
	driveInches( sqrt(2 * 24*24) );//drive forward
	startTask( mobileGoalIn ); //Task: MGL in
	delay( 500 );
	turnDegrees( -180 );
	driveInches( sqrt(2 * 24*24) + 6 );
	startTask( mobileGoalOut );//MGL out //Place mobile goal into 10 point zone
	delay( 1500 );

	//Task: MGL in
	driveInches( -sqrt(2 * 24*24) ); //drive backwards
	turnDegrees( 180 ); //Face towards the opposite side of where you started
	//startTask( mobileGoalOut ); //Task: MGL out
	//drive forward
	//startTask( mobileGoalIn ); //Task: MGL in
	//delay( 500 );
	//drive forward
	//turnDegreees( 90 );
	//drive forward
	//turnDegrees( -90 );
	//drive forward
	//startTask( mobileGoalOut ); //Task MGL out
	//delay( 1500 );
	//drive backward
	//Task MGL in
	//turnDegrees( 90 );
	//drive forward
	//turnDegrees( 45 );
	//Task MGL out
	//drive forward
	//Task MGL in
	//delay( 500 );
	//drive backward
	//turnDegrees( 180 );

}
