bStopTasksBetweenModes = true; //Set this to true

if(LCD_CONNECTED) {

	skillsEnabled = ynQuestion("Run Skills?");
	delay(500);

	autonOptions[0] = "None";
	autonOptions[1] = "Mobile";
	autonOptions[2] = "5 Point";
	autonOptions[3] = "10 point";

	if(!skillsEnabled) {
		leftStart = tfQuestion("Left Side?");
		delay(500);
		autoChoice = autonomousSelector();
	}

	//Clear the LCD
	clearLCD();
	//while(true)
		//displayLCDNumber(0,autoChoice);
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

setSlewRate(leftDrive, 20); //Set slew rate to 20
setSlewRate(rightDrive, 20); //Set slew rate to 20
