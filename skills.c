
task mobileGoalOut() {
	setSpeed(leftMobileGoal, 127);
	setSpeed(rightMobileGoal, 127);
	delay(1500);
	setSpeed(leftMobileGoal, 0);
	setSpeed(rightMobileGoal, 0);
}

task mobileGoalIn() {
	setSpeed(leftMobileGoal, -127);
	setSpeed(rightMobileGoal, -127);
	delay(1500);
	setSpeed(leftMobileGoal, 0);
	setSpeed(rightMobileGoal, 0);
}

task skillsTask1() {
	setDRFBAngle(-15);
	delay(500);
	startTask( mobileGoalOut );
}

void skills() {
	//auto4(); //20 point zone

	startTask( pidTask );

	//This is the same as the 20 point autonomous but faster
	startTask( skillsTask1 ); //Task: raise DRFB, MGL out
	driveInches( 55 ); //drive forward
	startTask( mobileGoalIn ); //Task: MGL in
	delay(500); //give time for MGL to be lifted off of the ground
	driveInches( -48 ); //drive backward
	turnDegrees( -45 );
	driveInches( -15 );//drive backward
	turnDegrees( -90 );
	driveInches( 13 ); //drive forward
	startTask( mobileGoalOut ); //MGL out //Place mobile goal into 20 point zone
	delay(1500); //let the mobile goal settle

	driveInches( -13 ); //drive backward
	startTask( mobileGoalIn ); //Task: MGL in
	turnDegrees( -90 );
	//drive forward
	//turnDegrees( -45 );
	//Task: MGL out
	//drive forward
	//Task: MGL in
	//delay(500);
	//drive backward
	//turnDegrees( -180 );
	//drive forward
	//MGL out //Place mobile goal into 10 point zone

	//drive backward
	//Task: MGL in
	//turnDegrees( 90 );
	//back up against wall
	//drive forward
	//turnDegrees( 45 );
	//Task: MGL out
	//drive forward
	//Task: MGL in
	//delay(500);
	//drive backwards
	//turnDegrees( -135 );
	//drive forward
	//MGL out //Place mobile goal into middle of 10 point zone

	//drive backward
	//Task: MGL in
	//turnDegrees( 90 );
	//drive forward
	//turnDegrees( 45 );
	//Task: MGL out
	//drive forward
	//Task: MGL in
	//delay(500);
	//turnDegrees( -180);
	//driveInches
	//MGL out //Place mobile goal into 10 point zone

	//drive backwards

}
