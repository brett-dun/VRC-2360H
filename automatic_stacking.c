
task automaticStacking() {

	while( true ) {


		//Raise DRFB and deliver cone
		disableDRFBPID();
		setSpeedImmediate(leftDRFB, 64);
		delay(100);
		while( getCleanUltrasonic() < 11 || getCleanUltrasonic() == -1 ) //test this value
			delay(20);
		setSpeedImmediate(leftDRFB, 0);

		setCBAngle(90); //raise chain bar
		delay(750); //wait for chain bar to finish moving
		setSpeedImmediate(leftDRFB, -127);
		delay(250);
		setSpeedImmediate(leftDRFB, 0);
		releaseCone(500); //release the cone


		//Lower DRFB and pickup cone
		setSpeedImmediate(leftDRFB, 127);
		delay(300);
		setSpeedImmediate(leftDRFB, 0);
		setCBAngle(0);
		delay(500);
		setDRFBAngle(-25);
		/*int prev = 0;
		setSpeedImmediate(intake, 64);
		do {
			prev = SensorValue[intakeEncoder];
			delay(100);
		} while( SensorValue[intakeEncoder] != prev );
		setSpeed(intake, 0);*/
		while( !vexRT[Btn6UXmtr2] ) //wait for button press
			delay(20);
		while( vexRT[Btn6UXmtr2] ) //wait for button release
			delay(20);

		delay(20);

	}

}
