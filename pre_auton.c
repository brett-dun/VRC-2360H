
void pre_auton() {

	init(); //Enable SmartMotor

	addSlave(leftDrive, leftMiddleDrive);
	addSlave(rightDrive, rightMiddleDrive);

	addSlave(leftMobileGoal, rightMobileGoal);

	nMotorEncoder[leftMobileGoal] = 0;

}
