/*****************************************************************/
int maxSpeed = 127; //the robot will start with its maximum speed
/*****************************************************************/

clearLCDLine(0); //Clear the top line of the LCD
clearLCDLine(1); //Clear the bottom line of the LCD
bLCDBacklight = false; //Turn the LCD's backlight off
displayLCDCenteredString(0, "2630H");
displayLCDCenteredString(1, "HELIX");

enable();

while(true) { //Run for the duration of the entire driver control period

	if(vexRT[Btn8U]) { //If button 8U is pressed
		maxSpeed = 127; //Change the maximum speed to 127 (maximum value)
	} else if(vexRT[Btn8L] || vexRT[Btn8R]) { //If buttons 8L or 8R are pressed
		maxSpeed = 64; //Change the maximum speed to 64 (1/2 of the maximum value)
	} else if(vexRT[Btn8D]) {
		maxSpeed = 32; //Change the maximum speed to 32 (1/4 of the maximum value)
	}

	setSpeed(frontLeftDrive, vexRT[Ch3] * maxSpeed / 127.0);
	setSpeed(frontRightDrive, vexRT[Ch2] * maxSpeed / 127.0);

	if(vexRT[Btn6U]) { //If button 6U is pressed
		setSpeed(drfbLeft, 127);
	} else if(vexRT[Btn6D]) { //If button 6D is pressed
		 setSpeed(drfbLeft, -127);
	} else {
		setSpeed(drfbLeft, 0);
	}

}
