#pragma systemFile //This prevents "Unreference variable" and "Unreferenced function" warnings

/*
	distance > 0 >>> forward
	distance < 0 >>> backward

	Status:
	- working

	Issues/Ideas:
	-
*/
void driveInches(float distance) {

	const float max = distance < 0 ? -127 : 127;
	const float ticks = fabs(distance / (WHEEL_DIAMETER * PI * DRIVE_RATIO) * TICKS); //will always be positive

	float leftTicks = 0;
	float rightTicks = 0;
	float average = 0;
	float speed = 0;

	nMotorEncoder[leftDrive] = 0;
	nMotorEncoder[rightDrive] = 0;

	while(leftTicks < ticks || rightTicks < ticks) {

		leftTicks = abs(nMotorEncoder[leftDrive]);
		rightTicks = abs(nMotorEncoder[rightDrive]);
		average = ( leftTicks + rightTicks ) / 2.0;

		speed = atan(0.01 * (ticks-average)) / (PI/2) * max;

		if(leftTicks < rightTicks) {
			setSpeed(leftDrive, speed);
			setSpeed(rightDrive, speed - atan(0.05 *(average-leftTicks)) / (PI/2) * speed);
		} else {
			setSpeed(leftDrive, speed - atan(0.05 *(average-rightTicks)) / (PI/2) * speed);
			setSpeed(rightDrive, speed);
		}

		delay(20);

	}

  setDrive(0);

}
