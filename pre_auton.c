
void pre_auton() {

	if(LCD_CONNECTED) {

		clearLCD(true);
		displayLCDCenteredString(0, "PLUG IN");
		displayLCDCenteredString(1, "BATTERY #2");
		while( SensorValue[powerExpander] < 500 );//No battery is attached

		skillsEnabled = ynQuestion("Run Skills?");
		delay(500);

		autonOptions[0] = "None";
		autonOptions[1] = "Mobile";
		autonOptions[2] = "Stationary";
		autonOptions[3] = "5 Point";
		autonOptions[4] = "10 Point";
		autonOptions[5] = "22 Point";

		if(!skillsEnabled) {
			leftStart = tfQuestion("Left Side?");
			delay(500);
			autoChoice = autonomousSelector();
		}

		clearLCD(true); //Clear the LCD
		displayLCDCenteredString(0, "Calibrating"); //Set top display
		displayLCDCenteredString(1, "DO NOT TOUCH"); //Set bottom display

	} else {
		leftStart = true; //start on left
		/*
		0 = none
		1 = mobile
		2 = stationary
		3 = 5 point
		4 = 10 point
		5 = 20 point
		*/
		autoChoice = 4;
	}

	/* Let's try to see how it works without calibration
	//Calibrate gyroscope
	SensorType[in1] = sensorNone; //Clear sensor port
	delay(1000); //Delay 2 sec
	SensorType[in1] = sensorGyro; //Enable gyroscope
	delay(2000); //Delay 2 sec*/


	init(); //Enable SmartMotor

	addSlave(leftDrive, leftMiddleDrive);
	addSlave(rightDrive, rightMiddleDrive);

	addSlave(leftDRFB, rightDRFB);

	addSlave(leftMobileGoal, rightMobileGoal);

	nMotorEncoder[leftDRFB] = 0;

}
