
void auto3() { //drop cone on mobile goal, move mobile goal to five point zone

	auto1();

	driveInches(-30);

	if(leftStart)
		turnDegrees(93);
	else
		turnDegrees(-93);

	driveInches(3);

	if(leftStart)
		turnDegrees(93);
	else
		turnDegrees(-93);

	driveInches(15);

	lowerMobileGoal();

	driveInches(-20);

}
