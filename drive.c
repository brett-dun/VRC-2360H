#pragma systemFile

//distance in inches
void drive(float distance) {

	const float KP = 15.; //Proportional constant
	const float KI = 0.03; //Integral constant
	const float KD = 0.00; //Derivative constant

	int leftOutput = 0; //Output for the left motor
	float leftError = 0; //Error on the left side
	/*float prevLeftError = 0; //Previous error on the left side
	float leftProportion = 0; //Proportion on the left side
	float leftIntegral = 0; //Integral on the left side
	float leftDerivative = 0; //Derivative on the left side*/

	int rightOutput = 0; //Output for the right motor
	float rightError = 0; //Error on the right side
	/*float prevRightError = 0; //Previous error on the right side
	float rightProportion = 0; //Proportion on the right side
	float rightIntegral = 0; //Integral on the right side
	float rightDerivative = 0; //Derviative on the right side*/

	float output = 0; //Output speed
	float error = 0;
	float prevError = 0; //Previous Error
	float proportion = 0;
	float integral = 0;
	float derivative = 0;

	nMotorEncoder[leftDrive] = 0; //Reset left motor encoder
	nMotorEncoder[rightDrive] = 0; //Reset right motor encoder

	while(true) {

		//prevLeftError = leftError; //Set the current error to the previous error
		leftError = distance - ( abs(nMotorEncoder(leftDrive)) / TICKS * WHEEL_DIAMETER * PI * DRIVE_RATIO ); //Calculate the new error for the left side

		/*leftProportion = leftError * KP; //Calculate the left side proportion
		leftIntegral += prevLeftError * KI;
		leftDerivative = (leftError - prevLeftError) * KD; //Calculate the left side derivative

		leftOutput = (int) (leftProportion + leftIntegral + leftDerivative); //Calculate the left side output
		leftOutput = distance > 0 ? leftOutput : -leftOutput;*/


		//prevRightError = rightError; //Set the current error to the previous error
		rightError = distance - ( abs(nMotorEncoder(rightDrive)) / TICKS * WHEEL_DIAMETER * PI * DRIVE_RATIO ); //Calculate the new error for the right side

		/*rightProportion = rightError * KP; //Calculate the right side proportion
		rightIntegral += prevRightError * KI;
		rightDerivative = (rightError - prevRightError) * KD; //Calculate the right side derivative

		rightOutput = (int) (rightProportion + rightIntegral + rightDerivative); //Calculate the right side output
		rightOutput = distance > 0 ? rightOutput : -rightOutput;
		leftOutput = rightOutput;*/


		prevError = error; //Set the current error to the previous error
		error = (leftError + rightError) / 2.0; //Calculate the new error

		proportion = error * KP; //Calculate the proportion
		integral += prevError * KI;
		derivative = (error - prevError) * KD; //Calculate the derivative

		output = proportion + integral + derivative; //Calculate the output

		if(output > 127)
			output = 127;
		if(distance < 0)
			output = -output;


		if(nMotorEncoder[leftDrive] > nMotorEncoder[rightDrive]) {
			leftOutput = (int) (output - atan( (error-leftError) ) / (PI/2) * output);
			rightOutput = (int) output;
		} else {
			leftOutput = (int) output;
			rightOutput = (int) (output - atan( (error-rightError) ) / (PI/2) * output);
		}


		//Exits loop when the robot has stopped and is within one inch of the target
		if(getMotorVelocity(leftDrive) == 0 && getMotorVelocity(rightDrive) == 0 && leftError < 0.5 && rightError < 0.5) {
			setDrive(0);
			return;
		}


		setDrive(leftOutput, rightOutput); //Set the motors to their speeds
		delay(20); //Wait for 20 ms

	}
}
