
task userTask() {
	skills();
}


task usercontrol() {

	enable(); //Enable the smart motors

	startTask(pidTask);
	startTask(userTask);

	while( !(vexRT[Btn5U] && vexRT[Btn5D] && vexRT[Btn6U] && vexRT[Btn6D]) )
		delay(20);

	stopTask(userTask);
	stopTask(pidTask);

	float speedMultiplier = 0.5; //the robot will start at half speed

	while(true) {

		if(vexRT[Btn8U]) //If button 8U is pressed
			speedMultiplier = 1.0; //Change the maximum speed to 100%
		else if(vexRT[Btn8L] || vexRT[Btn8R]) //If buttons 8L or 8R are pressed
			speedMultiplier = 0.75; //Change the maximum speed to 75%
		else if(vexRT[Btn8D]) //If button 8D is pressed
			speedMultiplier = 0.5; //Change the maximum speed to 50%

		setSpeed(leftDrive, vexRT[Ch3] * speedMultiplier); //Set leftDrive speed
		setSpeed(rightDrive, vexRT[Ch2] * speedMultiplier); //Set rightDrive speed*/

		/*if(abs(vexRT[Ch4]) > abs(vexRT[Ch2])) {
			setSpeed(leftDrive, vexRT[Ch4] * .33);
			setSpeed(rightDrive, -vexRT[Ch4] * .33);
		} else {
			setSpeed(leftDrive, vexRT[Ch2] * speedMultiplier);
			setSpeed(rightDrive, vexRT[Ch2] * speedMultiplier);
		}*/

		//Partner Controls
		if(vexRT[Btn5U])
			setSpeed(leftMobileGoal, 127);
		else if(vexRT[Btn5D])
			setSpeed(leftMobileGoal, -127);
		else
			setSpeed(leftMobileGoal, 0);

		if(vexRT[Btn6U])
			setSpeedImmediate(claw, 127); //intake cone
		else if(vexRT[Btn6D])
			setSpeedImmediate(claw, -127); //release cone
		else
			setSpeedImmediate(claw, 0);

		delay(20);

	}

}
