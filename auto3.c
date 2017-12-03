
void auto3() {

	auto1();

	raiseMobileGoal();
	delay(500);

	if(leftStart)
		turnDegrees(90);
	else
		turnDegrees(-90);

	driveInches(6);

	if(leftStart)
		turnDegrees(90);
	else
		turnDegrees(-90);

	driveInches(48);

	if(leftStart)
		turnDegrees(-45);
	else
		turnDegrees(45);

	driveInches(24);

	if(leftStart)
		turnDegrees(90);
	else
		turnDegrees(-90);

	driveInches(20);
	lowerMobileGoal();
	delay(500);
	driveInches(-12);
}

	/*
	//Defensive auton idea

	driveInches(-48);
	if(leftStart)
		turnDegrees(45);
	else
		turnDegrees(-45);
	driveInches( -sqrt(2) * 2 * 24 );*/
