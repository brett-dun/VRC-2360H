
void auto5() {

	auto1();

	driveInches(-48);

	if(leftStart)
		turnDegrees(135);
	else
		turnDegrees(-135);

	driveInches(15); //check this

	if(leftStart)
		turnDegrees(90);
	else
		turnDegrees(-90);

	driveInches(13);

	lowerMobileGoal();

	driveInches(-20);

}
