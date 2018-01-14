
void auto2() { //drop cone on mobile goal, move mobile goal to five point zone

	getMobileGoal();

	/*driveInches(-45);

	if(leftStart)
		turnDegrees(135);
	else
		turnDegrees(-135);

	driveInches(30);

	if(leftStart)
		turnDegrees(90);
	else
		turnDegrees(-90);

	driveInches(6);

	lowerMobileGoal();*/
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
