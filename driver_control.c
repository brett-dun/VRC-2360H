/*****************************************************************/
int maxSpeed = 64; //the robot will start with its maximum speed
int leftDRFB_speed = 0;
int rightDRFB_speed = 0;
/*****************************************************************/


clearLCD();
bLCDBacklight = false; //Turn the LCD's backlight off
displayLCDCenteredString(0, "2630H");
displayLCDCenteredString(1, "HELIX");

enable(); //Enable the smart motors


while(true) { //Run for the duration of the driver control period


	//Main Controller

	if(vexRT[Btn8U]) { //If button 8U is pressed
		maxSpeed = 127; //Change the maximum speed to 127 (maximum value)
	} else if(vexRT[Btn8L] || vexRT[Btn8R]) { //If buttons 8L or 8R are pressed
		maxSpeed = 127  * 0.75; //Change the maximum speed to 96
	} else if(vexRT[Btn8D]) { //If button 8D is pressed
		maxSpeed = 127 * 0.5; //Change the maximum speed to 64
	}

	setSpeed(leftDrive, vexRT[Ch3] * maxSpeed / 127.0); //Set leftDrive speed
	setSpeed(rightDrive, vexRT[Ch2] * maxSpeed / 127.0); //Set rightDrive speed

	if(SensorValue[leftDRFB_reset]) {
		nMotorEncoder[leftDRFB] = 0;
		leftDRFB_speed = 0;
	}

	if(SensorValue[rightDRFB_reset]) {
		nMotorEncoder[rightDRFB] = 0;
		rightDRFB_speed = 0;
	}

	if(vexRT[Btn6U]) { //If button 6U is pressed
		//leftDRFB_speed = nMotorEncoder[leftDRFB] > nMotorEncoder[rightDRFB] ? 96 : 127;
		//rightDRFB_speed = nMotorEncoder[leftDRFB] > nMotorEncoder[rightDRFB] ? 127 : 96;
		leftDRFB_speed = 127;
		rightDRFB_speed = 127;
	} else if(vexRT[Btn6D]) { //If button 6D is pressed
		leftDRFB_speed = -127;
		rightDRFB_speed = -127;
		//leftDRFB_speed = nMotorEncoder[leftDRFB] > nMotorEncoder[rightDRFB] ? -127 : -96;
		//rightDRFB_speed = nMotorEncoder[leftDRFB] > nMotorEncoder[rightDRFB] ? -96 : -127;
	} else { //Otherwise
		//leftDRFB_speed = nMotorEncoder[leftDRFB] > nMotorEncoder[rightDRFB] ? -16 : 16;
		//rightDRFB_speed = nMotorEncoder[leftDRFB] > nMotorEncoder[rightDRFB] ? 16 : -16;
		leftDRFB_speed = 0;
		rightDRFB_speed = 0;
	}

	setSpeed(leftDRFB, leftDRFB_speed);
	setSpeed(rightDRFB, rightDRFB_speed);

	/*if( (vexRT[Btn7U] || vexRT[Btn7L] || vexRT[Btn7R] || vexRT[Btn7D]) && liftEnabled ) { //If 5U or 5D is pressed and the lift is enabled
		SensorValue[mobileGoalLift] = !SensorValue[mobileGoalLift]; //change the mobile goal lift's state
		liftEnabled = false; //disable the mobile goal lift
		clearTimer(T1); //clear timer T1
	}

	if(time1(T1) > 600) { //If T1 has a value greater than 600 (ms)
		liftEnabled = true; //Enable mobile goal lift
	}*/

	if(vexRT[Btn7U])
		raiseMobileGoal();

	if(vexRT[Btn7D])
		lowerMobileGoal();


	if(vexRT[Btn5U]) { //If button 5U is pressed
		setSpeed(chainBar, 127); //Raise the chain bar
	} else if(vexRT[Btn5D]) { //If button 5D is pressed
		setSpeed(chainBar, -127); //Lower the chain bar
	} else { //Otherwise
		setSpeed(chainBar, 0); //Stop the chain bar
	}


	//Partner Controller
	//------------------


	if(vexRT[Btn6UXmtr2]) {
		setSpeed(intake, 127);
	} else if(vexRT[Btn6DXmtr2]) {
		setSpeed(intake, -127);
	} else {
		setSpeed(intake, 0);
	}

	delay(10);

}
