#pragma systemFile //This prevents "Unreference variable" and "Unreferenced function" warnings

//float temp = 0;

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

	const float speed = 48;
	float leftSpeed = rightTurn ? speed : -speed;
	float rightSpeed = -leftSpeed;

	//const float K = 0.05;

	while(fabs(absGyroValue-initial) < fabs(angle) ) {
		//float angleDifference = fabs(angle) - fabs(absGyroValue-initial);
		//setSpeed(leftDrive, leftSpeed * atan(K * fabs(angleDifference) ), true);
		//setSpeed(rightDrive, rightSpeed * atan(K * fabs(angleDifference) ), true);
		setSpeed(leftDrive, leftSpeed);
		setSpeed(rightDrive, rightSpeed);
		absGyroValue = fabs(SensorValue[in1]/10.0);
	}

	setSpeed(leftDrive, rightTurn ? -127: 127);
	setSpeed(rightDrive, rightTurn ? 127: -127);

	delay(250);

	setDrive(0);
}
