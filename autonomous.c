
task autonomous() {

	enable(); //Enable the smart motors

	turn( 90 );

	return;

	driveInches( 50 ); //drive forward
	startTask( mobileGoalUp ); //Task: MGL in
	delay(500); //try to shorten this

	driveInches( -45 ); //drive backward
	startTask( autoTask2 );

	turnDegrees( 150 );

	driveInches( 19 ); //drive forward

	turnDegrees( 75 );

	driveInches( 21 ); //drive forward - ram 20 point zone

	startTask( mobileGoalDown ); //Task: lower mobile goal

}
