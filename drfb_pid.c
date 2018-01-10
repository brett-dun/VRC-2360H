#pragma systemFile //This prevents "Unreference variable" and "Unreferenced function" warnings

static float targetAngle = 0;

void setDRFBAngle(float angle) {
	targetAngle = angle;
}

//For DRFB
task drfbPID() {

	const float KP = 1.3; //Proportional constant
	const float KI = 0.0; //Integral constant
	const float KD = 0.0; //Derivative constant

	int leftOutput = 0; //Output for the left motor
	float leftError = 0; //Error on the left side
	float prevLeftError = 0; //Previous error on the left side
	float leftProportion = 0; //Proportion on the left side
	float leftIntegral = 0; //Integral on the left side
	float leftDerivative = 0; //Derivative on the left side

	int rightOutput = 0; //Output for the right motor
	float rightError = 0; //Error on the right side
	float prevRightError = 0; //Previous error on the right side
	float rightProportion = 0; //Proportion on the right side
	float rightIntegral = 0; //Integral on the right side
	float rightDerivative = 0; //Derviative on the right side

	while(true) {

		prevLeftError = leftError; //Set the current error to the previous error
		rightError = targetAngle - ( abs(nMotorEncoder[leftDRFB]) / 627.2 * (1.0/7.0) * 360.0 ); //ticks/(ticks/rotation)*(Wout/Win)*(degrees/rotation)

		leftProportion = leftError * KP; //Calculate the left side proportion
		leftIntegral += prevLeftError * KI;
		leftDerivative = (leftError - prevLeftError) * KD; //Calculate the left side derivative

		leftOutput = (int) (leftProportion + leftIntegral + leftDerivative); //Calculate the left side output


		prevRightError = rightError; //Set the current error to the previous error
		rightError = targetAngle - ( abs(nMotorEncoder[rightDRFB]) / 627.2 * (1.0/7.0) * 360.0 ); //ticks/(ticks/rotation)*(Wout/Win)*(degrees/rotation)

		rightProportion = rightError * KP; //Calculate the right side proportion
		rightIntegral += prevRightError * KI;
		rightDerivative = (rightError - prevRightError) * KD; //Calculate the right side derivative

		rightOutput = (int) (rightProportion + rightIntegral + rightDerivative); //Calculate the right side output


		setDrive(leftOutput, rightOutput); //Set the motors to their speeds
		delay(20); //Wait for 20 ms

	}


}
