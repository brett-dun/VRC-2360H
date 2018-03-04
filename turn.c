#pragma systemFile //This prevents "Unreference variable" and "Unreferenced function" warnings

//angle is in degrees
void turn(float angle) {

	const float KP = 1.5; //Proportional constant
	const float KI = 0.; //Integral constant
	const float KD = 1.; //Derivative constant

	float output = 0; //Output speed
	float error = 0;
	float prevError = 0; //Previous Error
	float proportion = 0;
	float integral = 0;
	float derivative = 0;

	float previous = SensorValue[in1] / 10.0;
	float current = SensorValue[in1] / 10.0;
	float sum = 0;

	while(true) {

		previous = current;
		current = SensorValue[in1] / 10.0;
		sum += current - previous;

		error = fabs(angle) - fabs(sum); //Calculate the error

		proportion = error * KP; //Calculate the proportion
		integral += prevError * KI;
		derivative = (error - prevError) * KD; //Calculate the derivative

		//add some bounds to the integral
		integral = integral > 127 ? 127 : (integral < -127 ? -127 : integral);
		integral = (prevError <= 0. && error >= 0.) || (prevError >= 0. && error <= 0.) ? 0 : integral;

		output = proportion + integral + derivative; //Calculate the output
		output = output > 127 ? 127 : (output < -127 ? -127 : output);

		//Exit loop
		if(getMotorVelocity(leftDrive) == 0 && error < 0.5) {
			setDrive(0, true);
			return;
		}

		setDrive(angle > 0 ? output: -output, angle > 0 ? -output : output); //Set the drive to the output speed
		delay(20);

	}

}
