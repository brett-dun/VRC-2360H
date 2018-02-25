
void auto5() {

	getMobileGoal();

	driveInches( -30 ); //drive backward
	startTask( autoTask2 );

	turnDegrees( 135 );

	driveInches( 19 ); //drive forward

	turnDegrees( 90 );

	driveInches( 21 ); //drive forward - ram 20 point zone

	startTask( mobileGoalDown ); //Task: lower mobile goal

}
