
void skills() {

	auto5(); //first mobile goal into the 20 point zone

	//start working on the code here

	turnDegrees( -90 );
	driveInches( 15 ); //drive forward
	turnDegrees( -45 );
	driveInches( 30 ); //drive forward
	startTask( mobileGoalUp ); //Task: raise mobile goal lift

	//from 10 point
	driveInches(-30);

	turnDegrees(192.5); //190

	driveInches(9); //stop suddenly
	//

	driveInches( -12 ); //drive backward
	startTask( mobileGoalDown ); //Task: lower mobile goal lift
	turnDegrees( 90 );
	squareRobot();
	//setDrive( -64 ); //back up against wall
	delay( 2000 );
	setDrive( 0 );
	driveInches( 36 ); //drive forward
	//startTask( mobileGoalOut ); //Task: MGL out
	turnDegrees( 45 );
	driveInches( 12 );//drive forward
	startTask( mobileGoalUp ); //Task: MGL in
	delay(500);
	driveInches( -sqrt(2 * 24*24) ); //drive backwards
	turnDegrees( -135 );
	driveInches( 18 ); //drive forward - stop suddenly
	//startTask( mobileGoalOut ); //MGL out //Place mobile goal into middle of 10 point zone
	turnDegrees( -45 );
	delay( 750 );

	driveInches( -6 ); //drive backward
	startTask( mobileGoalDown ); //Task: MGL in
	turnDegrees( 90 );
	driveInches( sqrt(2 * 12*12) ); //drive forward
	turnDegrees( 90 );
	driveInches( sqrt(2 * 24*24) );//drive forward
	startTask( MobileGoalUp ); //Task: MGL in
	delay( 500 );
	turnDegrees( -180 );
	driveInches( sqrt(2 * 24*24) + 6 ); //stop suddenly
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
