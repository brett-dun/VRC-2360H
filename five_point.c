
void auto3() {

	auto1();

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

	//driveInches(10);

	lowerMobileGoal();

	driveInches(-20);

}
