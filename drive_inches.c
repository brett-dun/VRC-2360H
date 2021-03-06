#pragma systemFile //This prevents "Unreference variable" and "Unreferenced function" warnings

/*
	distance > 0 >>> forward
	distance < 0 >>> backward
*/
void driveInches(const float distance, const bool fast = false) {

	const int8 DIRECTION = distance < 0 ? -1 : 1;
	const float MAX_SPEED = 127. / 8.5 * 7.8 * DIRECTION;
	const float MIN_SPEED = fast ? MAX_SPEED : 32. * DIRECTION ;
	const float K1 = 0.001;
	const float K2 = 0.1;
	const float TARGET = fabs(distance / (WHEEL_DIAMETER * PI * DRIVE_RATIO) * TICKS); //will always be positive

	float leftTicks = 0;
	float rightTicks = 0;
	float average = 0;
	float speed = 0;

	//reset encoders to zero
	nMotorEncoder[leftDrive] = 0;
	nMotorEncoder[rightDrive] = 0;

	if(fast) {
		setSlewRate(leftDrive, 5);
		setSlewRate(rightDrive, 5);
	}

	while( true ) {

		//if we have passed the target
		if( average >= TARGET )
			break;

		//if the robot has nearly reached its target but is stopped
		if( !getMotorVelocity(leftDrive) && !getMotorVelocity(rightDrive) && fabs(TARGET-average) <= 0.5 / (WHEEL_DIAMETER * PI * DRIVE_RATIO) * TICKS )
			break;

		leftTicks = abs(nMotorEncoder[leftDrive]);
		rightTicks = abs(nMotorEncoder[rightDrive]);
		average = ( leftTicks + rightTicks ) / 2.0;

		speed = atan(K1 * (TARGET-average)) / (PI/2) * (MAX_SPEED-MIN_SPEED); //generate a bounded speed
		speed += MIN_SPEED; //add the minimum speed
		speed *= (8.5 / nAvgBatteryLevel * 1000.); //multiply by battery voltage factor

		//adjustments for if one side gets ahead
		if(leftTicks < rightTicks) {
			setSpeed(leftDrive, speed);
			setSpeed(rightDrive, speed - atan(K2 *(average-leftTicks)) / (PI/2) * speed);
		} else {
			setSpeed(leftDrive, speed - atan(K2 *(average-rightTicks)) / (PI/2) * speed);
			setSpeed(rightDrive, speed);
		}

		delay(20);

	}

	setSlewRate(leftDrive, 10);
	setSlewRate(rightDrive, 10);
  setDrive(0); //stop the drive

}
