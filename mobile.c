
task mobileGoalDown() {
	setSpeedImmediate(leftMobileGoal, -127);
	setSpeedImmediate(rightMobileGoal, -127);
	delay(2000);
	setSpeedImmediate(leftMobileGoal, 0);
	setSpeedImmediate(rightMobileGoal, 0);
}

task mobileGoalUp() {
	setSpeedImmediate(leftMobileGoal, 127);
	setSpeedImmediate(rightMobileGoal, 127);
	delay(2000);
	setSpeedImmediate(leftMobileGoal, 0);
	setSpeedImmediate(rightMobileGoal, 0);
}

//release cone
task autoTask2() {
	releaseCone(1000);
}
