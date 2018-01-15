
void auto2() {

	auto1();

	driveInches(-30);

	if(leftStart)
		turnDegrees(90);
	else
		turnDegrees(-90);

	driveInches(6);

	if(leftStart)
		turnDegrees(90);
	else
		turnDegrees(-90);

	driveInches(10);

	lowerMobileGoal();

	driveInches(-20);

}
