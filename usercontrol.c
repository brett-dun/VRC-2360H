
task usercontrol() {

	clearLCD();
	displayLCDCenteredString(0, "2630H");
	displayLCDCenteredString(1, "HELIX");

	enable(); //Enable the smart motors

	/*setSpeedImmediate(rightDRFB, 127);
	while( SensorValue[ultrasonic] < 6)
		delay(20);
	setSpeedImmediate(rightDRFB, 0);*/

	while(true) { //Run for the duration of the driver control period

		driverControl();

		startTask(pidTask);
		disableDRFBPID();

		semiAutonomous();

		stopTask(aTask);
		stopTask(bTask);
		stopTask(pidTask);

	}

}
