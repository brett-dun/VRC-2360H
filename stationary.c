
void returnMobileGoal() {

	driveInches(-20);

	if(leftStart)
		turnDegrees(93);
	else
		turnDegrees(-93);

	driveInches(3);

	if(leftStart)
		turnDegrees(93);
	else
		turnDegrees(-93);

	startTask( mobileGoalOut );
	delay(2000);

	driveInches(-20);

}


void auto2() {

	startTask(pidTask);

	driveInches( 6 );

	setDRFBAngle(10); //check this
	setCBAngle(0);

	delay(500);

	driveInches( 5 );

	releaseCone(1000); //Drop cone onto stationary goal

	driveInches( -5 ); //check this
	setDRFBAngle(-35);
	setCBAngle(90);
	startTask( mobileGoalOut );

	if(leftStart)
		turnDegrees( -135 );
	else
		turnDegrees( 135 );

	driveInches( 12*sqrt(2) );

	if(leftStart)
		turnDegrees( 45 );
	else
		turnDegrees( -45 );

	driveInches( 36 );
	startTask( mobileGoalIn );

	returnMobileGoal();

}
