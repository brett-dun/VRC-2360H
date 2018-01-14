#pragma systemFile //This prevents "Unreference variable" and "Unreferenced function" warnings

/*
	distance > 0 >>> forward
	distance < 0 >>> backward

	Status:
	- working

	Issues/Ideas:
	- inaccurate +/- 4%
*/
void driveInches(float distance) {

	const float max = distance < 0 ? -80 : 80;
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

		speed = max;

		if(leftTicks < rightTicks) {
			setSpeed(leftDrive, speed, false);
			setSpeed(rightDrive, speed - atan(0.1 *(average-leftTicks)) / (PI/2) * speed, false);
		} else {
			setSpeed(leftDrive, speed - atan(0.1 *(average-rightTicks)) / (PI/2) * speed, false);
			setSpeed(rightDrive, speed, false);
		}

	}

  /*setDrive(max < 0 ? 127 : -127);
  delay(100);*/
  setDrive(0);

}
