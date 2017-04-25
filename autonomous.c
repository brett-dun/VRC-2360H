SensorValue[sixBar] = 0;

//preload and first star - 10 points
openClaw(); //Open the claw to deploy the claw

delay(500); //Wait half of a second

driveInches(30); //Drive forward thirty inches

delay(250); //Wait a quarter of a second

closeClaw(); //Close the claw  on the two stars

startTask(raiseForklift); //Start raising the forklift

driveInches(30); //Drive forward thirty inches

startTask(maintainForkliftUp); //Keep the forklift raised

driveInches(6); //Drive forward six inches

openClaw(); //Open the claw to release the stars

delay(500); //Wait half of a second

driveInches(-12); //Drive backwards twelve inches

startTask(lowerForklift); //Begin to lower the forklift

squareRobot(); //Square the robot against the wall

middleCube(true); //Get the middle left cube - 10 points
middleCube(false); //Get the middle right cube - 10 points
outerCube(true); //Get the outer left cube - 10 points
outerCube(false); //Get the outer right cube - 10 points
stars(true); //Get the left side stars - 10 points
stars(false); //Get the right side stars - 10 points

//Goal: 70 points
