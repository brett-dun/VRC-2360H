#pragma systemFile //This prevents "Unreference variable" and "Unreferenced function" warnings

//#define WHEEL_DIAMETER 4.0
//#define DRIVE_RATIO 2.0
//#define TICKS 627.2


//Distance is in inches
void drive(float distance) {

	const float KP = 1.3;
	const float KI = 0.1;
	const float KD = 0.1;

	float leftOutput = 0;
	float leftError = 0;
	float prevLeftError = 0;
	float leftProportion = 0;
	float leftIntegral = 0;
	float leftDerivative = 0;

	float rightOutput = 0;
	float rightError = 0;
	float prevRightError = 0;
	float rightProportion = 0;
	float rightIntegral = 0;
	float rightDerivative = 0;

	nMotorEncoder[frontLeftDrive] = 0;
	nMotorEncoder[frontRightDrive] = 0;

	while(true) {

		prevLeftError = leftError;
		leftError = distance - ( abs(nMotorEncoder(frontLeftDrive)) / TICKS * WHEEL_DIAMETER * PI * DRIVE_RATIO );

		leftProportion = leftError * KP;
		leftIntegral = leftError == 0 ? 0 : (leftIntegral > 50.0/KI ? 50.0/KI : leftIntegral+prevLeftError*KI);
		leftDerivative = (leftError - prevLeftError) * KD;

		leftOutput = leftProportion + leftIntegral + leftDerivative;


		prevRightError = rightError;
		rightError = distance - ( abs(nMotorEncoder(frontRightDrive)) / TICKS * WHEEL_DIAMETER * PI * DRIVE_RATIO );

		rightProportion = rightError * KP;
		rightIntegral = rightError == 0 ? 0 : (rightIntegral > 50.0/KI ? 50.0/KI : rightIntegral+prevRightError*KI);
		rightDerivative = (rightError - prevRightError) * KD;

		rightOutput = rightProportion + rightIntegral + rightDerivative;


		/*if(leftError  < 1 && (int)rightError < 1) {
			setDrive(0, 0);
			return;
		}*/


		setDrive(rightOutput, rightOutput);
		delay(20);

	}
}
