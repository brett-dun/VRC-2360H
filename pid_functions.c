#pragma systemFile //This prevents "Unreference variable" and "Unreferenced function" warnings

//Distance is in inches
void drive(float distance) {

	const float KP = 1.3; //Proportional constant
	const float KI = 0.1; //Integral constant
	const float KD = 0.1; //Derivative constant

	float leftOutput = 0; //Output for the left motor
	float leftError = 0; //Error on the left side
	float prevLeftError = 0; //Previous error on the left side
	float leftProportion = 0; //Proportion on the left side
	float leftIntegral = 0; //Integral on the left side
	float leftDerivative = 0; //Derivative on the left side

	float rightOutput = 0; //Output for the right motor
	float rightError = 0; //Error on the right side
	float prevRightError = 0; //Previous error on the right side
	float rightProportion = 0; //Proportion on the right side
	float rightIntegral = 0; //Integral on the right side
	float rightDerivative = 0; //Derviative on the right side

	nMotorEncoder[leftDrive] = 0; //Reset left motor encoder
	nMotorEncoder[rightDrive] = 0; //Reset right motor encoder

	while(true) {

		prevLeftError = leftError; //Set the current error to the previous error
		leftError = distance - ( abs(nMotorEncoder(leftDrive)) / TICKS * WHEEL_DIAMETER * PI * DRIVE_RATIO ); //Calculate the new error for the left side

		leftProportion = leftError * KP; //Calculate the left side proportion
		leftIntegral = leftError == 0 ? 0 : (leftIntegral > 50.0/KI ? 50.0/KI : leftIntegral+prevLeftError*KI); //Calculate the left side integral
		leftDerivative = (leftError - prevLeftError) * KD; //Calculate the left side derivative

		leftOutput = leftProportion + leftIntegral + leftDerivative; //Calculate the left side output


		prevRightError = rightError; //Set the current error to the previous error
		rightError = distance - ( abs(nMotorEncoder(rightDrive)) / TICKS * WHEEL_DIAMETER * PI * DRIVE_RATIO ); //Calculate the new error for the right side

		rightProportion = rightError * KP; //Calculate the right side proportion
		rightIntegral = rightError == 0 ? 0 : (rightIntegral > 50.0/KI ? 50.0/KI : rightIntegral+prevRightError*KI); //Calculate the right side integral
		rightDerivative = (rightError - prevRightError) * KD; //Calculate the right side derivative

		rightOutput = rightProportion + rightIntegral + rightDerivative; //Calculate the right side output


		/*if(leftError  < 1 && (int)rightError < 1) {
			setDrive(0, 0);
			return;
		}*/


		setDrive(distance > 0 ? rightOutput : -rightOutput, distance > 0 ? rightOutput : -rightOutput); //Set the motors to their speeds
		delay(20); //Wait for 20 ms

	}
}


//Angle is in degrees
void turn(float angle) {

	const float KP = 1.3; //Proportional constant
	const float KI = 0.1; //Integral constant
	const float KD = 0.1; //Derivative constant

	float output = 0; //Output speed
	float error = 0;
	float prevError = 0; //Previous Error
	float proportion = 0;
	float integral = 0;
	float derivative = 0;

	while(true) {

		float initial = abs(SensorValue[in1]/10.0); //The initial angle
		float absGyroValue = abs(SensorValue[in1]/10.0); //Absolute value of the current gyroscope reading

		error = abs(angle) - abs(absGyroValue-initial); //Calculate the error

		proportion = error * KP; //Calculate the proportion
		integral = error == 0 ? 0 : (integral > 50.0/KI ? 50.0/KI : integral+prevError*KI); //Calculate the integral
		derivative = (error - prevError) * KD; //Calculate the derivative

		output = proportion + integral + derivative; //Calculate the output

		setDrive(angle > 0 ? output: -output, angle > 0 ? -output : output); //Set the drive to the output speed

	}

	setAllDrive(0); //Stop the drive


}
