void backStars(bool leftStart) {
	openClaw();
	delay(500);
	startTask(maintainForkliftDown);
	driveInches(22.5);
	startTask(maintainForkliftDown);
	driveInches(22.5);
	closeClaw();
	delay(100);
	driveInches(-45);
	startTask(raiseForklift);

	if(leftStart)
		targetAngle(90,false);
	else
		targetAngle(270,true);

	driveInches(37);
	startTask(maintainForkliftUp);
	driveInches(30);

	openClaw();
	delay(200);
	squareRobot();
	driveInches(12);

	if(leftStart)
		targetAngle(185,false);
	else
		targetAngle(175,true);

	startTask(lowerForklift);
	driveInches(6);
	startTask(maintainForkliftDown);
	delay(1200);
	closeClaw();
	delay(200);
	driveInches(-6);

	if(leftStart)
		targetAngle(110,true);
	else
		targetAngle(250,false);

	startTask(raiseForklift);
	driveInches(50);
	startTask(maintainForkliftUp);
	driveInches(10);
	openClaw();
}
