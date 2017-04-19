void frontStars(bool leftStart) {
	openClaw();
	delay(500);
	closeClaw();
	startTask(raiseForklift);
	driveInches(65);
	openClaw(); //Drop stars
	delay(200);
	squareRobot();
	driveInches(12);

	if(leftStart)
		targetAngle(80,false);
	else
		targetAngle(280,true);

	startTask(lowerForklift);
	driveInches(6);
	delay(1200);
	closeClaw();
	delay(200);
	driveInches(-6);

	if(leftStart)
		targetAngle(20,true);
	else
		targetAngle(340,false);

	startTask(raiseForklift);
	driveInches(63);
	openClaw();

}
