/*****************************************************************/
int maxSpeed = 64; //the robot will start with its maximum speed
bool liftEnabled = true; //mobile goal lift is enabled
/*****************************************************************/


clearLCDLine(0); //Clear the top line of the LCD
clearLCDLine(1); //Clear the bottom line of the LCD
bLCDBacklight = false; //Turn the LCD's backlight off
displayLCDCenteredString(0, "2630H");
displayLCDCenteredString(1, "HELIX");

enable(); //Enable the smart motors


while(true) { //Run for the duration of the driver control period


	//Main Controller

	if(vexRT[Btn8U]) { //If button 8U is pressed
		maxSpeed = 127; //Change the maximum speed to 127 (maximum value)
	} else if(vexRT[Btn8L] || vexRT[Btn8R]) { //If buttons 8L or 8R are pressed
		maxSpeed = 127 / 1.6 * 0.75; //Change the maximum speed to 96
	} else if(vexRT[Btn8D]) { //If button 8D is pressed
		maxSpeed = 127 * 0.5; //Change the maximum speed to 64
	}

	setSpeed(leftDrive, vexRT[Ch3] * maxSpeed / 127.0); //Set leftDrive speed
	setSpeed(rightDrive, vexRT[Ch2] * maxSpeed / 127.0); //Set rightDrive speed

	if(vexRT[Btn6U]) { //If button 6U is pressed
		setSpeed(leftDRFB, 127); //Raise double reverse four bar
	} else if(vexRT[Btn6D]) { //If button 6D is pressed
		 setSpeed(leftDRFB, -127); //Lower double reverse four bar
	} else { //Otherwise
		setSpeed(leftDRFB, 0); //Stop double reverse four bar
	}

	if( (vexRT[Btn5U] || vexRT[Btn5D]) && liftEnabled ) { //If 5U or 5D is pressed and the lift is enabled
		SensorValue[mobileGoalLift] = !SensorValue[mobileGoalLift]; //change the mobile goal lift's state
		liftEnabled = false; //disable the mobile goal lift
		clearTimer(T1); //clear timer T1
	}

	if(time1(T1) > 600) { //If T1 has a value greater than 600 (ms)
		liftEnabled = true; //Enable mobile goal lift
	}


	//Partner Controller
	//------------------

	if(vexRT[Btn5UXmtr2]) { //If button 5U is pressed
		setSpeed(chainBar, 127); //Raise the chain bar
	} else if(vexRT[Btn5DXmtr2]) { //If button 5D is pressed
		setSpeed(chainBar, -127); //Lower the chain bar
	} else { //Otherwise
		setSpeed(chainBar, 0); //Stop the chain bar
	}

	/*if(vexRT[Btn6UXmtr2] || vexRT[Btn6DXmtr2]) { //If button 6U or 6D is pressed
		if(SensorValue[clawButton]) //If the limit switch is pressed
			setSpeed(claw,32); //Maintain position
		else //If it is not pressed
			setSpeed(claw, 64); //Move the claw more
	} else { //Otherwise
			setSpeed(claw, 0); //Allow the claw to be pulled closed
	}*/
	if(vexRT[Btn6UXmtr2]) {
		setSpeed(claw, 127);
	} else if(vexRT[Btn6DXmtr2]) {
		setSpeed(claw, -127);
	} else {
		setSpeed(claw, 0);
	}

}
