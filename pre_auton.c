
void pre_auton() {

	bStopTasksBetweenModes = true; //Set this to true - check to see if we can delete this line

	if(LCD_CONNECTED) {

		skillsEnabled = ynQuestion("Run Skills?");
		delay(500);

		autonOptions[0] = "None";
		autonOptions[1] = "Mobile";
		autonOptions[2] = "Stationary";
		autonOptions[3] = "5 Point";
		autonOptions[4] = "10 Point";
		autonOptions[5] = "20 Point";

		if(!skillsEnabled) {
			leftStart = tfQuestion("Left Side?");
			delay(500);
			autoChoice = autonomousSelector();
		}

		clearLCD(true); //Clear the LCD
		displayLCDCenteredString(0, "Calibrating"); //Set top display
		displayLCDCenteredString(1, "DO NOT TOUCH"); //Set bottom display

	}

	//Calibrate gyroscope
	SensorType[in1] = sensorNone; //Clear sensor port
	delay(2000); //Delay 2 sec
	SensorType[in1] = sensorGyro; //Enable gyroscope
	delay(2000); //Delay 2 sec


	init(); //Enable SmartMotor

	addSlave(leftDrive, leftMiddleDrive);
	addSlave(rightDrive, rightMiddleDrive);

	addSlave(rightDRFB, leftDRFB);

	addSlave(leftMobileGoal, rightMobileGoal);

}
