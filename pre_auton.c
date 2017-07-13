bStopTasksBetweenModes = true; //Set this to true

//Clear the LCD
clearLCDLine(0);
clearLCDLine(1);
bLCDBacklight = true; //Turn the LCD's bakclight on
displayLCDCenteredString(0, "None"); //Set top display
displayLCDCenteredString(1, "<-  Select  ->"); //Set bottom display

while(nLCDButtons != 2) {

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

//calibrate gyroscope
SensorType[in1] = sensorNone;
delay(2000);
SensorType[in1] = sensorGyro;
delay(2000);


init(); //enable SmartMotor

addSlave(drfb1, drfb2, 0); //combine double reverse four bar motors

addSlave(leftDrive1, leftDrive2, 0); //combine left drive motors
addSlave(leftDrive1, leftDrive3, 1); //combine left drive motors

addSlave(rightDrive1, rightDrive2, 0); //combine right drive motors
addSlave(rightDrive1, rightDrive3, 1); //combine right drive motors
