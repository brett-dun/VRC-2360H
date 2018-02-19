
task automaticStacking() {

	while( true ) {


		//Raise DRFB and deliver cone
		/*setSpeedImmediate(rightDRFB, 127);
		while( SensorValue[ultrasonic] < 10) //test this value
			delay(20);
		setSpeed(rightDRFB, 0);*/
		setDRFBAngle(0); //figure out how to determine this
		delay(1000); //shorten this

		setCBAngle(90); //raise chain bar
		delay(750); //wait for chain bar to finish moving
		releaseCone(750); //release the cone


		//Lower DRFB and pickup cone
		setCBAngle(0);
		delay(1000);
		setDRFBAngle(-35);
		int prev = 0;
		setSpeedImmediate(intake, 64);
		do {
			prev = SensorValue[intakeEncoder];
			delay(100);
		} while( SensorValue[intakeEncoder] != prev );
		setSpeed(intake, 0);

		delay(20);

	}

}
