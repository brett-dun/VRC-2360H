
void auto1() { //Drop cone on mobile goal
	lowerMobileGoal();
	driveInches(66);
	delay(500);
	intakeCone(1000, true); //release cone
}
