#include "drivetrain_movement.h"

void pidDrive(float inches) {

  const float KP = 1.3;
	const float KI = 0.1;
	const float KD = 0.1;

  int leftEncoder = 0;
	float leftOutput = 0;
	float leftError = 0;
	float prevLeftError = 0;
	float leftProportion = 0;
	float leftIntegral = 0;
	float leftDerivative = 0;

  int rightEncoder = 0;
	float rightOutput = 0;
	float rightError = 0;
	float prevRightError = 0;
	float rightProportion = 0;
	float rightIntegral = 0;
	float rightDerivative = 0;

	//imeDriveReset();

	while(true) {

    //imeDriveGet(&leftEncoder, &rightEncoder);

		prevLeftError = leftError;
		leftError = inches - abs( leftEncoder  / DRIVE_TICKS * WHEEL_DIAMETER * PI * DRIVETRAIN_GR );

		leftProportion = leftError * KP;
		leftIntegral = leftError == 0 ? 0 : (leftIntegral > 50.0/KI ? 50.0/KI : leftIntegral+prevLeftError*KI);
		leftDerivative = (leftError - prevLeftError) * KD;

		leftOutput = leftProportion + leftIntegral + leftDerivative;


		prevRightError = rightError;
		rightError = inches - abs( rightEncoder * DRIVETRAIN_GR * WHEEL_DIAMETER * PI  / DRIVE_TICKS  );

		rightProportion = rightError * KP;
		rightIntegral = rightError == 0 ? 0 : (rightIntegral > 50.0/KI ? 50.0/KI : rightIntegral+prevRightError*KI);
		rightDerivative = (rightError - prevRightError) * KD;

		rightOutput = rightProportion + rightIntegral + rightDerivative;


		if(abs(leftError) < 1.0 && abs(rightError) < 1.0) {
			setDrive(0, 0);
			return;
		}


		setDrive(inches > 0 ? leftOutput : -leftOutput, inches > 0 ? rightOutput : -rightOutput);
		delay(20);

	}
}
