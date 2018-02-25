
void auto4() { //drop cone on mobile goal, move mobile goal to five point zone

	auto1();

	driveInches(-30);

	if(leftStart)
		turnDegrees(192.5); //190
	else
		turnDegrees(-192.5);

	driveInches(9);
	delay(100);
	startTask( mobileGoalOut );
	delay(2000);

	driveInches(-20);

}
