
void auto3() {

	auto1();

	driveInches(-30);

	if(leftStart)
		turnDegrees(190);
	else
		turnDegrees(-190);

	startTask( mobileGoalOut );
	delay(2000);

	driveInches(-20);

}
