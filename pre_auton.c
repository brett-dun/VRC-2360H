
void pre_auton() {

	if(LCD_CONNECTED) {

		clearLCD(true);
		displayLCDCenteredString(0, "PLUG IN");
		displayLCDCenteredString(1, "BATTERY #2");
		while( SensorValue[powerExpander] < 500 ) //No battery is attached
			delay(20);

		playTone(440, 100);
		delay(100);
		playTone(440, 100);
		delay(100);
		playTone(440, 100);

		skillsEnabled = ynQuestion("Run Skills?");
		delay(500);

		autonOptions[0] = "None";
		autonOptions[1] = "Mobile";
		autonOptions[2] = "Stationary";
		autonOptions[3] = "5+6 Point";
		autonOptions[4] = "10+6 Point";
		autonOptions[5] = "20+4 Point";

		if(!skillsEnabled) {
			leftStart = tfQuestion("Left Side?");
			delay(500);
			autoChoice = autonomousSelector();
		}

		clearLCD(true); //Clear the LCD
		displayLCDCenteredString(0, leftStart ? "Left" : "Right"); //Set top display
		displayLCDCenteredString(1, autonOptions[autoChoice]); //Set bottom display

	} else {
		leftStart = true; //start on left
		/*
		0 = none
		1 = mobile
		2 = stationary
		3 = 11 point
		4 = 16 point
		5 = 24 point
		*/
		autoChoice = 5;
	}

	init(); //Enable SmartMotor

	addSlave(leftDrive, leftMiddleDrive);
	addSlave(rightDrive, rightMiddleDrive);

	addSlave(leftDRFB, rightDRFB);

	addSlave(leftMobileGoal, rightMobileGoal);

	nMotorEncoder[leftDRFB] = 0;

}
