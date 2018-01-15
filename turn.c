#pragma systemFile

//angle is in degrees
void turn(float angle) {

	const float KP = 2.; //Proportional constant
	const float KI = 0.; //Integral constant
	const float KD = 0.02; //Derivative constant

	int output = 0; //Output speed
	float error = 0;
	float prevError = 0; //Previous Error
	float proportion = 0;
	float integral = 0;
	float derivative = 0;

	float initial = fabs(SensorValue[in1]/10.0); //The initial angle

	while(true) {

		float absGyroValue = fabs(SensorValue[in1]/10.0); //Absolute value of the current gyroscope reading

		error = fabs(angle) - fabs(absGyroValue-initial); //Calculate the error

		proportion = error * KP; //Calculate the proportion
		integral += prevError * KI;
		derivative = (error - prevError) * KD; //Calculate the derivative

		output = (int) (proportion + integral + derivative); //Calculate the output

		//Exit loop
		if(getMotorVelocity(leftDrive) == 0 && error < 0.5) {
			setDrive(0);
			return;
		}

		setDrive(angle > 0 ? output: -output, angle > 0 ? -output : output); //Set the drive to the output speed
		delay(20);

	}

}
