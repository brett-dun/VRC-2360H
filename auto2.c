
void auto2() { //drop cone on mobile goal, move mobile goal to five point zone

	auto1();

	raiseMobileGoal();
	delay(500);

	driveInches(-30);

	delay(500);

	if(leftStart)
		turnDegrees(90);
	else
		turnDegrees(-90);

	driveInches(6);

	if(leftStart)
		turnDegrees(90);
	else
		turnDegrees(-80);

	driveInches(30); //reduce this?
	lowerMobileGoal();

	setSpeed(leftDRFB, 127);
	setSpeed(rightDRFB, 127);
	delay(500);
	setSpeed(leftDRFB, 0);
	setSpeed(rightDRFB, 0);

	delay(500);
	driveInches(-24);
}
