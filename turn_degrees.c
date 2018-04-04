#pragma systemFile //This prevents "Unreference variable" and "Unreferenced function" warnings

/*
	angle > 0 >>> right
	angle < 0 >>> left
*/
void turnDegrees(float angle) {

	angle -= 10. * atan(0.03 * angle);

	SensorValue[gyro] = 0;

	const int8 DIRECTION = angle > 0 ? 1 : -1;
	const float MAX_SPEED = 64. / 8.5 * 7.8 * DIRECTION;
	const float MIN_SPEED = 0. * DIRECTION;
	const float K = 0.2; //constant for arctangent function

	float angleDifference = angle; //how much the robot still needs to turn
	float speed = 0;

	while( true ) {

		//we have turned more than we wanted to
		if( fabs(SensorValue[gyro]/10.) >= fabs(angle) ) {
			setDrive(-127 * DIRECTION, 127 * DIRECTION);
			delay(75);
			break;
		}

		//we are close but the motors have stopped
		if( !getMotorVelocity(leftDrive) && !getMotorVelocity(rightDrive) && fabs(angleDifference) <= 2.)
			break;

		angleDifference = fabs(angle) - fabs(SensorValue[gyro]/10.); //calculate the difference between the desired angle and the target angle

		speed = atan(K * angleDifference) / (PI/2) * (MAX_SPEED-MIN_SPEED); //generate a bounded speed
		speed += MIN_SPEED; //add the minimum speed
		speed *= (8.5 / nAvgBatteryLevel * 1000.); //multiply by battery voltage factor

		setSpeed(leftDrive, speed);
		setSpeed(rightDrive, -speed);

		delay(20);

	}

	setDrive(0);
	delay(250);

}
