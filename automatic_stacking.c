
task automaticStacking() {

	while( vexRT[Btn7L] ) {


		//Raise DRFB and deliver cone
		setSpeedImmediate(rightDRFB, 127);
		while( SensorValue[ultrasonic] < 6) //this will change
			delay(20);
		setSpeedImmediate(rightDRFB, 0);

		setCBAngle(90); //raise drfb
		delay(750); //wait for chain bar to finish moving
		releaseCone(500); //release the cone


		//Lower DRFB and pickup cone
		setCBAngle(0);
		delay(750);

		setSpeedImmediate(rightDRFB, -127);
		setSpeedImmediate(intake, 127);
		delay(100);

		while( getMotorVelocity(rightDRFB) != 0 || getMotorVelocity(intake) != 0) {

			if(getMotorVelocity(rightDRFB) == 0)
				setSpeedImmediate(rightDRFB, 0);

			if(getMotorVelocity(intake) == 0)
				setSpeedImmediate(intake, 0);

				delay(20);
		}

		setSpeedImmediate(rightDRFB, 0);
		setSpeedImmediate(intake, 0);

		delay(20);

	}

}
