bStopTasksBetweenModes = true; //Set this to true

SensorType[in1] = sensorNone;
delay(2000);
SensorType[in1] = sensorGyro;
delay(2000);


SmartMotorsInit();

SmartMotorLinkMotors(forklift1, forklift2);
SmartMotorLinkMotors(forklift1, forklift3);
SmartMotorLinkMotors(forklift1, forklift4);
//SmartMotorLinkMotors(forklift1, forklift5);

SmartMotorsSetEncoderGearing(forklift1, 5); //check this ratio
SmartMotorPtcMonitorEnable();

SmartMotorSetSlewRate(backLeft, 255);
//SmartMotorSetSlewRate(frontLeft, 255);
SmartMotorSetSlewRate(backRight, 255);
//SmartMotorSetSlewRate(frontRight, 255);

SmartMotorRun();
