
void lowerMobileGoal() {
	setSpeed(leftMobileGoal, 127);
	setSpeed(rightMobileGoal, 127);
	delay(1500);
	setSpeed(leftMobileGoal, 0);
	setSpeed(rightMobileGoal, 0);
}

void raiseMobileGoal() {
	setSpeed(leftMobileGoal, -127);
	setSpeed(rightMobileGoal, -127);
	delay(1500);
	setSpeed(leftMobileGoal, 0);
	setSpeed(rightMobileGoal, 0);
}

task mobileGoalTask() {
	setSpeed(leftMobileGoal, 127);
	setSpeed(rightMobileGoal, 127);
	setSpeed(leftDRFB, 127);
	setSpeed(rightDRFB, 127);

	delay(500);

	setSpeed(leftMobileGoal, 0);
	setSpeed(rightMobileGoal, 0);
	setSpeed(leftDRFB, 0);
	setSpeed(rightDRFB, 0);
}

void getMobileGoal() {

	startTask(mobileGoalTask);

	driveInches(55);

	raiseMobileGoal();

	intakeCone(1000, true);

}

void auto1() {

	getMobileGoal();

	driveInches(-30);

	if(leftStart)
		turnDegrees(90);
	else
		turnDegrees(-90);

	driveInches(6);

	if(leftStart)
		turnDegrees(90);
	else
		turnDegrees(-90);

	driveInches(10);

	lowerMobileGoal();

	driveInches(-20);

}
