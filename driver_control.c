

void driverControl() {

	float speedMultiplier = 0.5; //the robot will start at half speed

	while(true) {

		if(vexRT[Btn8U]) //If button 8U is pressed
			speedMultiplier = 1.0; //Change the maximum speed to 100%
		else if(vexRT[Btn8L] || vexRT[Btn8R]) //If buttons 8L or 8R are pressed
			speedMultiplier = 0.5; //Change the maximum speed to 50%
		else if(vexRT[Btn8D]) //If button 8D is pressed
			speedMultiplier = 0.35; //Change the maximum speed to 35%

		setSpeed(leftDrive, vexRT[Ch3] * speedMultiplier); //Set leftDrive speed
		setSpeed(rightDrive, vexRT[Ch2] * speedMultiplier); //Set rightDrive speed

		if(vexRT[Btn6U]) //If button 6U is pressed
			setSpeedImmediate(rightDRFB, 127);
		else if(vexRT[Btn6D]) //If button 6D is pressed
			setSpeedImmediate(rightDRFB, -127);
		else //Otherwise
			setSpeedImmediate(rightDRFB, 0);

		if(vexRT[Btn5UXmtr2]) //Partner
			setSpeed(leftMobileGoal, -127);
		else if(vexRT[Btn5DXmtr2]) //Partner
			setSpeed(leftMobileGoal, 64);
		else if(vexRT[Btn7U]) //Main
			setSpeed(leftMobileGoal, -127);
		else if(vexRT[Btn7D]) //Main
			setSpeed(leftMobileGoal, 127);
		else
			setSpeed(leftMobileGoal, 0);

		if(vexRT[Btn5U])//If button 5U is pressed
			setSpeedImmediate(chainBar, 127); //Raise the chain bar
		else if(vexRT[Btn5D]) //If button 5D is pressed
			setSpeedImmediate(chainBar, -127); //Lower the chain bar
		else //Otherwise
			setSpeedImmediate(chainBar, 0); //Stop the chain bar

		if(vexRT[Btn6UXmtr2])
			setSpeedImmediate(intake, 127); //intake cone
		else if(vexRT[Btn6DXmtr2])
			setSpeedImmediate(intake, -127); //release cone
		else
			setSpeedImmediate(intake, 0);

		if( vexRT[Btn7LXmtr2]&&vexRT[Btn7RXmtr2] )
			return;

		delay(20);

	}

}
