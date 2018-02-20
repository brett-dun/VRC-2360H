
task automaticStacking() {

	while( true ) {

		//Raise DRFB and deliver cone
		disableDRFBPID();
		setSpeedImmediate(leftDRFB, 127);
		delay(100);
		while( getCleanUltrasonic() < 11 )
			delay(50);
		setSpeed(leftDRFB, 0);

		setCBAngle(90); //raise chain bar
		delay(750); //wait for chain bar to finish moving - reduce this?
		setSpeedImmediate(leftDRFB, -127);
		delay(250);
		setSpeedImmediate(leftDRFB, 0);
		releaseCone(550); //release the cone
		setSpeedImmediate(leftDRFB, 127);
		delay(300);
		setSpeedImmediate(leftDRFB, 0);
		setCBAngle(0);
		delay(500);
		setDRFBAngle(-20);

		while( !vexRT[Btn6UXmtr2] ) //wait for button press
			delay(20);
		while( vexRT[Btn6UXmtr2] ) //wait for button release
			delay(20);

	}

}
