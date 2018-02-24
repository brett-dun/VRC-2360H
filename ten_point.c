
void auto4() { //drop cone on mobile goal, move mobile goal to five point zone

	auto1();

	driveInches(-30);

	if(leftStart)
		turnDegrees(180);
	else
		turnDegrees(-180);

	driveInches(7.5);
	delay(100);
	startTask( mobileGoalOut );
	delay(2000);

	driveInches(-20);

}
