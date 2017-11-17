bStopTasksBetweenModes = true; //Set this to true

if(LCD_CONNECTED) {

	//Clear the LCD
	clearLCDLine(0);
	clearLCDLine(1);
	bLCDBacklight = true; //Turn the LCD's bakclight on
	displayLCDCenteredString(0, "Run Skills?"); //Set top display
	displayLCDCenteredString(1, "Yes       No"); //Set bottom display

	while(true) { //Run until something causes this loop to exit

		if(nLCDButtons == 1) { //Left button
			skillsEnabled = true; //Activate robot skills mode
			return; //Exit the loop
		}

		if(nLCDButtons == 4) //Right button
			return; //Exit the loop

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
					case 4: displayLCDCenteredString(0, "Nothing"); break; //No autonomous will run
				}
				delay(250); //Delay 250 ms
			}

			if(nLCDButtons == 4) { //Right button
				autoChoice++; //Increment the choice
				if(autoChoice > 4) { //If it is greater than three
					autoChoice = 4; //Set it to one
				}
				switch(autoChoice) { //Select code based on this variable
					case 4: displayLCDCenteredString(0, "Nothing"); break; //No autonomous will run
				}
				delay(250); //Delay 250 ms
			}

		}

	}

	//Clear the LCD
	clearLCDLine(0);
	clearLCDLine(1);
	displayLCDCenteredString(0, "Calibrating"); //Set top display
	displayLCDCenteredString(1, "DO NOT TOUCH"); //Set bottom display

}

//Calibrate gyroscope
SensorType[in1] = sensorNone; //Clear sensor port
delay(2000); //Delay 2 sec
SensorType[in1] = sensorGyro; //Enable gyroscope
delay(2000); //Delay 2 sec


init(); //Enable SmartMotor

setSlewRate(leftDrive, 20); //Set slew rate to 20
setSlewRate(rightDrive, 20); //Set slew rate to 20
