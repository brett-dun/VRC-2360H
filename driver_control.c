/*
	Main Controller
	---------------
		Joysticks:
			1	[None]
			2	Right Drive Control
			3	Left Drive Control
			4	[None]
		Buttons:
			5U && 5D	Claw Control
				5U -> Change Claw State
				5D ->
			6U && 6D Forklift Control
				6U -> Raise Forklift
				6D -> Lower Forklift
			7U && 7L && 7R && 7D  [None]
				7U ->
				7L && 7R ->
				7D ->
			8U && 8L && 8R && 8D Variable Drive Speed Control
				8U -> 128 maxSpeed
				8L && 8R -> 96 maxSpeed
				8D -> 64 maxSpeed
*/

/*****************************************************************/
int maxSpeed = 128; //the robot will start with its maximum speed
int enableClaw = 1; //the claw is ready to be used
//int speed = 0;
/*****************************************************************/

clearTimer(T1); //Clear the timer

//Clear the LCD
clearLCDLine(0);
clearLCDLine(1);
bLCDBacklight = true; //Turn the LCD's backlight off
displayLCDCenteredString(0, "2630H");
displayLCDCenteredString(1, "HELIX");

while(true) { //Run for the duration of the entire driver control period

	gyroValue = SensorValue[in1] / 10.0;

	if(vexRT[Btn8U]) { //If button 8U is pressed
		maxSpeed = 128; //Change the maximum speed to 128 (maximum value)
	} else if(vexRT[Btn8L] || vexRT[Btn8R]) { //If buttons 8L or 8R are pressed
		maxSpeed = 96; //Change the maximum speed to 64 (1/2 of the maximum value)
	} else if(vexRT[Btn8D]) {
		maxSpeed = 64; //Change the maximum speed to 32 (1/4 of the maximum value)
	}

	SetMotor(backLeft, vexRT[Ch3] * maxSpeed / 128.0);
	SetMotor(frontLeft, vexRT[Ch3] * maxSpeed / 128.0);
	SetMotor(backRight, vexRT[Ch2] * maxSpeed / 128.0);
	SetMotor(frontRight, vexRT[Ch2] * maxSpeed / 128.0);

	if(vexRT[Btn6U]) { //If button 6U is pressed
		setAllForklift(128);
	} else if(vexRT[Btn6D]) { //If button 6D is pressed
		 if(SensorValue[sixBar] > 36) {
			setAllForklift(-128);
		} else if(SensorValue[sixBar] > 24) {
			setAllForklift(-96);
		} else if(SensorValue[sixBar] > 12) {
			setAllForklift(-64);
		} else {
			setAllForklift(-32);
		}
	} else {
		setAllForklift(0);
	}

	if(vexRT[Btn5U] && enableClaw) { //If button 5U is pressed and enable claw has a non-zero value
		SensorValue[claw] = !SensorValue[claw]; //
		enableClaw = 0; //Set the value of enable claw to zero
		clearTimer(T1); //Clear the timer
	}

	if(time1(T1) > 600) { //If T1 has a value greater than 250 (ms)
		enableClaw = 1; //Set the value of enable claw to one
	}

}
