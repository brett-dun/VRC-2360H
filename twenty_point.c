
void auto5() {

	auto1();

	driveInches(-60);

	if(leftStart)
		turnDegrees(135);
	else
		turnDegrees(-135);

	driveInches(12); //check this

	if(leftStart)
		turnDegrees(90);
	else
		turnDegrees(-90);

	driveInches(24); //check this

	lowerMobileGoal();

	driveInches(-20);

}
