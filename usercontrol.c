
task usercontrol() {

	enable(); //Enable the smart motors

	float speedMultiplier = 0.5; //the robot will start at half speed

	while(true) {

		if(vexRT[Btn8U]) //If button 8U is pressed
			speedMultiplier = 1.0; //Change the maximum speed to 100%
		else if(vexRT[Btn8L] || vexRT[Btn8R]) //If buttons 8L or 8R are pressed
			speedMultiplier = 0.75; //Change the maximum speed to 75%
		else if(vexRT[Btn8D]) //If button 8D is pressed
			speedMultiplier = 0.5; //Change the maximum speed to 50%

		setSpeed(leftDrive, vexRT[Ch3] * speedMultiplier); //Set leftDrive speed
		setSpeed(rightDrive, vexRT[Ch2] * speedMultiplier); //Set rightDrive speed


		//Partner Controls
		if(vexRT[Btn5UXmtr2])
			setSpeed(leftMobileGoal, -127);
		else if(vexRT[Btn5DXmtr2])
			setSpeed(leftMobileGoal, 127);
		else if(vexRT[Btn7DXmtr2])
			setSpeed(leftMobileGoal, 64); //Is there actually a need for this?
		else
			setSpeed(leftMobileGoal, 0);

		if(vexRT[Btn6UXmtr2])
			setSpeedImmediate(intake, 127); //intake cone
		else if(vexRT[Btn8UXmtr2])
			setSpeedImmediate(intake, 40);
		else if(vexRT[Btn6DXmtr2])
			setSpeedImmediate(intake, -127); //release cone
		else
			setSpeedImmediate(intake, 0);

		delay(20);

	}

}
