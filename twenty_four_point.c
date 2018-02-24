
void auto6() { //drop cone on mobile goal, move mobile goal to five point zone

	auto1();
	driveInches( -22 ); //drive backward

	if(leftStart)
		turnDegrees( -45 );
	else
		turnDegrees( 45 );

	driveInches( -37 ); //drive backward

	if(leftStart)
		turnDegrees( -90 );
	else
		turnDegrees( 90 );

	driveInches( 17 ); //drive forward
	//Place mobile goal into 20 point zone
	setSpeedImmediate(leftMobileGoal, 127);
	delay( 1000 ); //let the mobile goal settle - try to shorten this
	driveInches( -10 ); //drive backward
	setSpeed(leftMobileGoal, 0);

	startTask( mobileGoalIn ); //Task: MGL in

}
