#pragma systemFile //This prevents "Unreference variable" and "Unreferenced function" warnings

//distance in inches
void drive(float distance) {

	const float KP = 10.; //Proportional constant
	const float KI = 0.; //Integral constant
	const float KD = 1.; //Derivative constant

	int leftOutput = 0; //Output for the left motor
	float leftError = 0; //Error on the left side

	int rightOutput = 0; //Output for the right motor
	float rightError = 0; //Error on the right side

	float output = 0; //Output speed
	float error = 0;
	float prevError = 0; //Previous Error
	float proportion = 0;
	float integral = 0;
	float derivative = 0;

	nMotorEncoder[leftDrive] = 0; //Reset left motor encoder
	nMotorEncoder[rightDrive] = 0; //Reset right motor encoder

	while(true) {

		leftError = distance - ( abs(nMotorEncoder(leftDrive)) / TICKS * WHEEL_DIAMETER * PI * DRIVE_RATIO ); //Calculate the new error for the left side
		rightError = distance - ( abs(nMotorEncoder(rightDrive)) / TICKS * WHEEL_DIAMETER * PI * DRIVE_RATIO ); //Calculate the new error for the right side


		prevError = error; //Set the current error to the previous error
		error = (leftError + rightError) / 2.0; //Calculate the new error

		proportion = error * KP; //Calculate the proportion
		integral += prevError * KI;
		derivative = (error - prevError) * KD; //Calculate the derivative

		output = proportion + integral + derivative; //Calculate the output
		output = output > 127 ? 127 : (output < -127 ? -127 : output);
		output = distance < 0 ? -output : output;


		/*if(nMotorEncoder[leftDrive] > nMotorEncoder[rightDrive]) {
			leftOutput = (int) (output - atan( 8.0*(error-leftError) ) / (PI/2) * output);
			rightOutput = (int) output;
		} else {
			leftOutput = (int) output;
			rightOutput = (int) (output - atan( 8.0*(error-rightError) ) / (PI/2) * output);
		}*/
		leftOutput = output;
		rightOutput = output;


		//Exits loop when the robot has stopped and is within one inch of the target
		if(getMotorVelocity(leftDrive) == 0 && getMotorVelocity(rightDrive) == 0 && leftError < 0.5 && rightError < 0.5) {
			setDrive(0);
			return;
		}


		setDrive(leftOutput, rightOutput, true); //Set the motors to their speeds
		delay(20); //Wait for 20 ms

	}

}
