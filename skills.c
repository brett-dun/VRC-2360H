void skills() {
	cube(true);
	delay(100);
	driveInches(-21);
	targetAngle(325,true);
	squareRobot();
	startTask(lowerForklift);
	driveInches(36);

	for(int i = 0; i < 4; i++) {
		targetAngle(240,true);
		startTask(maintainForkliftDown);
		delay(2000);
		closeClaw();
		delay(100);
		startTask(raiseForklift);
		targetAngle(50,false);
		startTask(maintainForkliftUp);
		driveInches(31);
		startTask(maintainForkliftUp);
		driveInches(15);
		openClaw();
		delay(100);
		driveInches(-20);
		startTask(lowerForklift);
	}
}
