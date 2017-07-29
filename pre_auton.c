bStopTasksBetweenModes = true; //Set this to true

if(LCD_CONNECTED) {

	//Clear the LCD
	clearLCDLine(0);
	clearLCDLine(1);
	bLCDBacklight = true; //Turn the LCD's bakclight on
	displayLCDCenteredString(0, "Run Skills?"); //Set top display
	displayLCDCenteredString(1, "Yes       No"); //Set bottom display

	while(true) {

		if(nLCDButtons == 1) { //Left button
			skillsEnabled = true;
			return;
		}

		if(nLCDButtons == 4) { //Right button
			return;
		}

	}

	if(!skillsEnabled) {
		//Clear the LCD
		clearLCDLine(0);
		clearLCDLine(1);
		displayLCDCenteredString(0, "None"); //Set top display
		displayLCDCenteredString(1, "<-  Select  ->"); //Set bottom display

		while(nLCDButtons != 2 && !skillsEnabled) {

			if(nLCDButtons == 1) { //Left button
				autoChoice--; //Decrement the choice
				if(autoChoice < 4) { //If it is less than one
					autoChoice = 4; //Set it to three
				}
				switch(autoChoice) { //Select code based on this variable
					case 4: displayLCDCenteredString(0, "Nothing"); break;
				}
				delay(250);
			}

			if(nLCDButtons == 4) { //Right button
				autoChoice++; //Increment the choice
				if(autoChoice > 4) { //If it is greater than three
					autoChoice = 4; //Set it to one
				}
				switch(autoChoice) {
					case 4: displayLCDCenteredString(0, "Nothing"); break;
				}
				delay(250);
			}

		}

	}

	//Clear the LCD
	clearLCDLine(0);
	clearLCDLine(1);
	displayLCDCenteredString(0, "Calibrating"); //Set top display
	displayLCDCenteredString(1, "DO NOT TOUCH"); //Set bottom display

}

//calibrate gyroscope
SensorType[in1] = sensorNone;
delay(2000);
SensorType[in1] = sensorGyro;
delay(2000);


init(); //enable SmartMotor

addSlave(drfbLeft, drfbRight); //combine double reverse four bar motors

addSlave(frontLeftDrive, middleLeftDrive); //combine left drive motors
addSlave(frontLeftDrive, backLeftDrive); //combine left drive motors

addSlave(frontRightDrive, middleRightDrive); //combine right drive motors
addSlave(frontRightDrive, backRightDrive); //combine right drive motors
