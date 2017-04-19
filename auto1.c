void cube(bool leftStart) {

	openClaw(); //Deploy Claw
	delay(250);
	startTask(maintainForkliftDown);
	closeClaw();
	driveInches(10);

	/*if(leftStart) //Turn to move star out of the way
		targetAngle(340,true);
	else
		targetAngle(20,false);

	if(leftStart) //Turn back to original position
		targetAngle(0,false);
	else
		targetAngle(0,true);*/

	openClaw();
	driveInches(23);
	closeClaw(); //Grab Cube
	startTask(raiseForklift);
	driveInches(14);

	if(leftStart) //Turn towards fence
		targetAngle(45,false);
	else
		targetAngle(315,true);

	startTask(maintainForkliftUp);
	driveInches(40);
	openClaw(); //Drop cube
	delay(200);
	driveInches(-24);

	if(leftStart)
		targetAngle(0,true);
	else
		targetAngle(0,false);

	startTask(lowerForklift);
	driveInches(-64);

	if(leftStart) //Turn towards stars
		targetAngle(310,true);
	else
		targetAngle(50,false);

	startTask(maintainForkliftDown);
	driveInches(25);
	startTask(maintainForkliftDown);
	driveInches(25);
	closeClaw(); //Grab stars

	if(leftStart) //Turn towards fence
		targetAngle(50,false);
	else
		targetAngle(310,true);

	startTask(raiseForklift);
	driveInches(55);
	motor[backLeft] = 128;
	motor[frontLeft] = 128;
	motor[backRight] = 128;
	motor[frontRight] = 128;

	delay(500);

	motor[backLeft] = 0;
	motor[frontLeft] = 0;
	motor[backRight] = 0;
	motor[frontRight] = 0;
	openClaw(); //Drop stars
}
