
void pre_auton() {

	/* Let's try to see how it works without calibration
	//Calibrate gyroscope
	SensorType[in1] = sensorNone; //Clear sensor port
	delay(1000); //Delay 2 sec
	SensorType[in1] = sensorGyro; //Enable gyroscope
	delay(2000); //Delay 2 sec*/


	init(); //Enable SmartMotor

	addSlave(leftDrive, leftMiddleDrive);
	addSlave(rightDrive, rightMiddleDrive);

	addSlave(leftMobileGoal, rightMobileGoal);

}
