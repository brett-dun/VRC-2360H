#pragma systemFile //This prevents "Unreference variable" and "Unreferenced function" warnings

//Distance is in inches
void drive(float distance) {

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

	nMotorEncoder[leftDrive] = 0; //Reset left motor encoder
	nMotorEncoder[rightDrive] = 0; //Reset right motor encoder

	while(true) {

		prevLeftError = leftError; //Set the current error to the previous error
		leftError = distance - ( abs(nMotorEncoder(leftDrive)) / TICKS * WHEEL_DIAMETER * PI * DRIVE_RATIO ); //Calculate the new error for the left side

		leftProportion = leftError * KP; //Calculate the left side proportion
		//leftIntegral = leftError == 0 ? 0 : (leftIntegral > 50.0/KI ? 50.0/KI : leftIntegral+prevLeftError*KI); //Calculate the left side integral
		leftIntegral += prevLeftError * KI;
		leftDerivative = (leftError - prevLeftError) * KD; //Calculate the left side derivative

		leftOutput = (int) (leftProportion + leftIntegral + leftDerivative); //Calculate the left side output


		prevRightError = rightError; //Set the current error to the previous error
		rightError = distance - ( abs(nMotorEncoder(rightDrive)) / TICKS * WHEEL_DIAMETER * PI * DRIVE_RATIO ); //Calculate the new error for the right side

		rightProportion = rightError * KP; //Calculate the right side proportion
		//rightIntegral = rightError == 0 ? 0 : (rightIntegral > 50.0/KI ? 50.0/KI : rightIntegral+prevRightError*KI); //Calculate the right side integral
		rightIntegral += prevRightError * KI;
		rightDerivative = (rightError - prevRightError) * KD; //Calculate the right side derivative

		rightOutput = (int) (rightProportion + rightIntegral + rightDerivative); //Calculate the right side output


		//Exits loop when the robot has stopped and is within one inch of the target
		if(leftOutput == 0 && rightOutput == 0 && leftError < 1.0 && rightError < 1.0)
			return;


		setDrive(distance > 0 ? leftOutput : -leftOutput, distance > 0 ? rightOutput : -rightOutput); //Set the motors to their speeds
		delay(20); //Wait for 20 ms

	}
}


//Angle is in degrees
void turn(float angle) {

	const float KP = 1.3; //Proportional constant
	const float KI = 0.0; //Integral constant
	const float KD = 0.0; //Derivative constant

	int output = 0; //Output speed
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
		//integral = error == 0 ? 0 : (integral > 50.0/KI ? 50.0/KI : integral+prevError*KI); //Calculate the integral
		integral += prevError * KI;
		derivative = (error - prevError) * KD; //Calculate the derivative

		output = (int) (proportion + integral + derivative); //Calculate the output

		//Exit loop
		if(output == 0 && error < 1)
			return;

		setDrive(angle > 0 ? output: -output, angle > 0 ? -output : output); //Set the drive to the output speed
		delay(20);

	}

}



static float targetAngle = 0;

void setDRFBAngle(float angle) {
	targetAngle = angle;
}

task maintainDRFBHeight() {

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

		if(SensorValue[leftDRFB_reset])
			nMotorEncoder[leftDRFB] = 0;

		if(SensorValue[rightDRFB_reset])
			nMotorEncoder[rightDRFB] = 0;

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
