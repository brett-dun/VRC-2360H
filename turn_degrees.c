#pragma systemFile //This prevents "Unreference variable" and "Unreferenced function" warnings

void turnDegrees(float angle){

	bool rightTurn = angle > 0;

	float previous = SensorValue[in1] / 10.0;
	float current = SensorValue[in1] / 10.0;
	float sum = 0;
	float angleDifference = angle;

	const float speed = 45;
	float leftSpeed = rightTurn ? speed : -speed;
	float rightSpeed = -leftSpeed;

	const float K = 0.05;

	while( fabs(sum) < fabs(angle) ) {

		previous = current;
		current = SensorValue[in1] / 10.0;
		sum += current - previous;

		angleDifference = fabs(angle) - fabs(sum);

		setSpeed(leftDrive, leftSpeed * atan(K * fabs(angleDifference) ), true);
		setSpeed(rightDrive, rightSpeed * atan(K * fabs(angleDifference) ), true);

	}

	/*setSpeed(leftDrive, rightTurn ? -127: 127);
	setSpeed(rightDrive, rightTurn ? 127: -127);

	delay(250);*/

	setDrive(0);
}
