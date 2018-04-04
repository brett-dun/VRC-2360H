
void auto5() {

	getMobileGoal();

	driveInches( -30 ); //drive backward
	startTask( autoTask2 );

	if(leftStart)
		turnDegrees( -45 );
	else
		turnDegrees( 45 );

	driveInches( -19 );

	if(leftStart)
		turnDegrees( -90 );
	else
		turnDegrees( 90 );

	driveInches( 21 ); //drive forward
	//Place mobile goal into 20 point zone
	setSpeedImmediate(leftMobileGoal, 127);
	delay( 1000 ); //let the mobile goal settle - try to shorten this
	driveInches( -10 ); //drive backward
	setSpeed(leftMobileGoal, 0);

	startTask( mobileGoalIn ); //Task: MGL in

}
