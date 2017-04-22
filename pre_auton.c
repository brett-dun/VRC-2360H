bStopTasksBetweenModes = true; //Set this to true

//Clear the LCD
clearLCDLine(0);
clearLCDLine(1);
bLCDBacklight = true; //Turn the LCD's bakclight on
displayLCDCenteredString(0, "Autonomous:"); //Display "Autonomous:" on the top
displayLCDCenteredString(1, "None"); //Display "None" on the bottom

while(nLCDButtons != 2) {

	if(nLCDButtons == 1) { //Left button
		autoChoice--; //Decrement the choice
		if(autoChoice < 1) { //If it is less than one
			autoChoice = 7; //Set it to three
		}
		switch(autoChoice) { //Select code based on this variable
			case 1: displayLCDCenteredString(1, "Left - Cube"); break;
			case 2: displayLCDCenteredString(1, "Left - Back"); break;
			case 3: displayLCDCenteredString(1, "Left - Front"); break;
			case 4: displayLCDCenteredString(1, "Nothing"); break;
			case 5: displayLCDCenteredString(1, "Right - Cube"); break;
			case 6: displayLCDCenteredString(1, "Right - Back"); break;
			case 7: displayLCDCenteredString(1, "Right - Front"); break;
		}
		delay(250);
	}

	if(nLCDButtons == 4) { //Right button
		autoChoice++; //Increment the choice
		if(autoChoice > 7) { //If it is greater than three
			autoChoice = 1; //Set it to one
		}
		switch(autoChoice) {
			case 1: displayLCDCenteredString(1, "Left - Cube"); break;
			case 2: displayLCDCenteredString(1, "Left - Back"); break;
			case 3: displayLCDCenteredString(1, "Left - Front"); break;
			case 4: displayLCDCenteredString(1, "Nothing"); break;
			case 5: displayLCDCenteredString(1, "Right - Cube"); break;
			case 6: displayLCDCenteredString(1, "Right - Back"); break;
			case 7: displayLCDCenteredString(1, "Right - Front"); break;
		}
		delay(250);
	}

}

SensorType[in1] = sensorNone;
delay(2000);
SensorType[in1] = sensorGyro;
delay(2000);


SmartMotorsInit();

SmartMotorLinkMotors(forklift1, forklift2);
SmartMotorLinkMotors(forklift1, forklift3);
SmartMotorLinkMotors(forklift1, forklift4);
SmartMotorLinkMotors(forklift1, forklift5);

SmartMotorsSetEncoderGearing(forklift1, 5); //check this ratio
SmartMotorsAddPowerExtender(5, 7, 5, 9); //check to see whether port five needs to be here twice
SmartMotorPtcMonitorEnable();

SmartMotorSetSlewRate(backLeft, 255);
SmartMotorSetSlewRate(frontLeft, 255);
SmartMotorSetSlewRate(backRight, 255);
SmartMotorSetSlewRate(frontRight, 255);

SmartMotorRun();
