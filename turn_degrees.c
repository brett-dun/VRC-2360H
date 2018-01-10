#pragma systemFile //This prevents "Unreference variable" and "Unreferenced function" warnings

/*
	angle > 0 >>> clockwise
	angle < 0 >>> counterclockwise

	Status:
	- testing required

	Issues/Ideas:
	- inaccurate +/- 5 degrees
*/
void turnDegrees(float angle){

	bool rightTurn = angle > 0;

	float initial = fabs(SensorValue[in1]/10.0);
	float absGyroValue = fabs(SensorValue[in1]/10.0);

	const float speed = 127;
	float leftSpeed = rightTurn ? speed : -speed;
	float rightSpeed = -leftSpeed;

	const float K = 0.05;

	while(fabs(absGyroValue-initial) < fabs(angle) ) {
		float angleDifference = fabs(angle) - fabs(absGyroValue-initial);
		setSpeed(leftDrive, leftSpeed * atan(K * fabs(angleDifference) ), true);
		setSpeed(rightDrive, rightSpeed * atan(K * fabs(angleDifference) ), true);
		absGyroValue = fabs(SensorValue[in1]/10.0);
	}

	setSpeed(leftDrive, rightTurn ? -127: 127, true);
	setSpeed(rightDrive, rightTurn ? 127: -127, true);

	delay(100);

	setDrive(0);
}
