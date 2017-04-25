void middleCube(bool left) {

	driveInches(15); //Drive forward fifteen inches

	if(left)
		turnDegrees(30); //Turn thirty degrees counter clockwise
	else
		turnDegrees(-30); //Turn thirty degrees clockwise

	driveInches(sqrt(3)*24); //Drive forward sqrt(3) * 24 inches

	delay(250); //Wait a quarter of a second

	closeClaw(); //Close the claw on the cube

	startTask(raiseForklift); //Begin to raise the forklift

	if(left)
		turnDegrees(-120); //Turn one hundred twenty degrees clockwise
	else
		turnDegrees(120); //Turn one hundred twenty degrees counter clockwise

	driveInches(24); //Drive forward twenty four inches

	if(left)
		turnDegrees(90); //Turn ninety degrees counter clockwise
	else
		turnDegrees(-90); //Turn ninety degrees clockwise

	driveInches(21); //Drive forward twenty one degrees

	startTask(maintainForkliftUp); //Keep the forklift up

	driveInches(6); //Drive forward six inches

	openClaw(); //Open the claw to drop the cube

	delay(500); //Wait half of a second

	driveInches(-12); //Drive backwards twelve inches

	startTask(lowerForklift); //Begin to lower the forklift

	squareRobot(); //Square the robot against the wall

}
