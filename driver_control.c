
task usercontrol() {


	float speedMultiplier = 0.5; //the robot will start at half speed


	clearLCD();
	displayLCDCenteredString(0, "2630H");
	displayLCDCenteredString(1, "HELIX");

	enable(); //Enable the smart motors


	while(true) { //Run for the duration of the driver control period


		//driver control
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
				setSpeed(rightDRFB, 127, true);
			else if(vexRT[Btn6D]) //If button 6D is pressed
				setSpeed(rightDRFB, -127, true);
			else //Otherwise
				setSpeed(rightDRFB, 0, true);

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
				setSpeed(chainBar, 127, true); //Raise the chain bar
			else if(vexRT[Btn5D]) //If button 5D is pressed
				setSpeed(chainBar, -127, true); //Lower the chain bar
			else //Otherwise
				setSpeed(chainBar, 0, true); //Stop the chain bar

			if(vexRT[Btn6UXmtr2])
				setSpeed(intake, 127, true);
			else if(vexRT[Btn6DXmtr2])
				setSpeed(intake, -127, true);
			else
				setSpeed(intake, 0, true);

			if(false)
				break;

			delay(20);

		}


		startTask(pidTask);
		//semi-autonomous
		while(true) {

			setSpeed(leftDrive, vexRT[Ch3] * 0.35); //Set leftDrive speed
			setSpeed(rightDrive, vexRT[Ch2] * 0.35); //Set rightDrive speed

			if(false) {//button1

				setCBAngle(90); //extend chain bar
				delay(500);
				setDRFBAngle(-30); //lower drfb

				//intake cone
				setSpeed(chainBar, -127, true);
				while( getMotorVelocity(chainBar) != 0);
				setSpeed(chainBar, 0, true);

			}

			if(false) {//button2
				setDRFBAngle(10); //raise drfb - add 3 height settings
			}

			if(false) { //button3

				setCBAngle(0); //retract chain bar
				delay(500);
				//setDRFBAngle(10);//lower drfb 3 height settings
				intakeCone(1000, true);

			}

			if(true) //button 4
				break;

			delay(20);

		}

		stopTask(pidTask);


	}


}
