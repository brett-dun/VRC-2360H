void outerCube(bool left) {

	driveInches(39); //Drive forward thirty nine inches

	if(left)
		turnDegrees(90); //Turn ninety degrees counter clockwise
	else
		turnDegrees(-90); //Turn ninety degrees clockwise

	driveInches(36); //Drive forward thrity six degrees

	delay(250); //Wait a quarter of a second

	closeClaw(); //Close the claw to grab the cube

	startTask(raiseForklift); //Begin to raise the forklift

	driveInches(-36); //Drive backwards thrity six inches

	if(left)
		turnDegrees(-90); //Turn ninety degrees clockwise
	else
		turnDegrees(90); //Turn ninety degrees counter clockwise

	driveInches(45); //Drive forward fourty five inches

	startTask(maintainForkliftUp); //Keep the forklift raised

	driveInches(6); //Drive forward six inches

	openClaw(); //Open the claw to drop the cube

	delay(500); //Wait half of a second

	driveInches(-12); //Drive backwards for twelve inches

	startTask(lowerForklift); //Begin to lower the forklift

	squareRobot(); //Square the robot against the wall

}
