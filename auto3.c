void stars(bool left) {

	driveInches(15); //Drive forward fifteen inches

	if(left)
		turnDegrees(90); //Turn ninety degrees counter clockwise
	else
		turnDegrees(-90); //Turn ninety degrees clockwise

	driveInches(39); //Drive forward thrity nine inches

	delay(250); //Wait half of a second

	if(left)
		turnDegrees(-90); //Turn ninety degrees clockwise
	else
		turnDegrees(90); //Turn ninety degrees counter clockwise

	driveInches(39); //Drive forward thrity nine inches

	if(left)
		turnDegrees(-90); //Turn ninety degrees clockwise
	else
		turnDegrees(90); //Turn ninety degrees counter clockwise

	driveInches(21); //Drive forward twenty one inches

	startTask(maintainForkliftUp); //Keep the forklift raised

	driveInches(6); //Drive forward six inches

	openClaw(); //Drop the stars

	delay(500); //Wait half of a second

	driveInches(-12); //Drive backwards twelve inches

	startTask(lowerForklift); //Begin to lower the forklift

	squareRobot(); //Square the robot against the wall

}
