#pragma systemFile //This prevents "Unreference variable" and "Unreferenced function" warnings

//#define WHEEL_DIAMETER 4.0

float gyroValue;

void setAllDrive(int speed) {
	setSpeed(frontLeftDrive, speed, true);
	setSpeed(frontRightDrive, speed, true);
}

void setDrive(float leftSpeed, float rightSpeed) {
	setSpeed(frontLeftDrive, leftSpeed, true);
	setSpeed(frontRightDrive, rightSpeed, true);
}

/*
	distance > 0 >>> forward
	distance < 0 >>> backward

	Status:
	- testing required

	Issues/Ideas:
	- use PID control
*/
void driveInches(float distance) {

	const float max = distance < 0 ? -80 : 80;
	const float ticks = fabs(distance / (WHEEL_DIAMETER * PI) * 392); //will always be positive

	float leftTicks = 0;
	float rightTicks = 0;
	float average = 0;
	float speed = 0;

	while(leftTicks < ticks || rightTicks < ticks) {

		leftTicks = abs(SensorValue[leftEncoder]);
		rightTicks = abs(SensorValue[rightEncoder]);
		average = ( leftTicks + rightTicks ) / 2.0;

		speed = max;//atan(0.05*(ticks - average)) / (PI/2) * max;

		if(leftTicks < rightTicks) {
			setSpeed(frontLeftDrive, speed, true);
			setSpeed(frontRightDrive, speed - atan(0.5 *(average-leftTicks)) / (PI/2) * speed, true);
		} else {
			setSpeed(frontLeftDrive, speed - atan(0.5 *(average-rightTicks)) / (PI/2) * speed, true);
			setSpeed(frontRightDrive, speed, true);
		}

	}

  setAllDrive(0);

}



/*
	Status:
	- testing required

	Issues/Ideas:
	-
*/
void squareRobot() {
	while(!SensorValue[leftTouch] || !SensorValue[rightTouch]) {

		if(SensorValue[leftTouch])
			setSpeed(frontLeftDrive, 0, true);
		else
			setSpeed(frontLeftDrive, -127, true);

		if(SensorValue[rightTouch])
			setSpeed(frontRightDrive, 0, true);
		else
			setSpeed(frontRightDrive, -127, true);

	}
	setAllDrive(0);
}



/*
	angle > 0 >>> clockwise
	angle < 0 >>> counterclockwise

	Status:
	-

	Issues/Ideas:
	-
*/
void turnDegrees(float angle){

	bool rightTurn = angle > 0;

	float initial = abs(SensorValue[in1]/10.0);
	float absGyroValue = abs(SensorValue[in1]/10.0);

	const float speed = 127;
	float leftSpeed = rightTurn ? speed : -speed;
	float rightSpeed = -leftSpeed;

	const float K = 0.05;

	while(abs(absGyroValue-initial) < abs(angle) ) {
		setSpeed(frontLeftDrive, leftSpeed * atan(K * abs(angle - gyroValue)), true);
		setSpeed(frontRightDrive, rightSpeed * atan(K * abs(angle - gyroValue)), true);
		absGyroValue = abs(SensorValue[in1]/10.0);
	}

	setSpeed(frontLeftDrive, rightTurn ? -127: 127, true);
	setSpeed(frontRightDrive, rightTurn ? 127: -127, true);

	delay(100);

	setAllDrive(0);
}



/*
	angle > 0 >>> clockwise
	angle < 0 >>> counterclockwise

	Status:
	- testing required

	Issues/Ideas:
	-Try to avoid using this function, it will eventually malfunction because of gyro drift
*/
void targetAngle(float angle, bool rightTurn){

	const float speed = rightTurn ? -80 : 80;

	float leftSpeed = -speed;
	float rightSpeed = speed;

	while( gyroValue < angle - 0.5 || gyroValue > angle + 0.5) {

		gyroValue = SensorValue[in1] / 10.0;
		if(gyroValue < 0)
			gyroValue = 360 + gyroValue;
		//gyroValue = gyroValue < 0 ? 360 - gyroValue : gyroValue;

		setSpeed(frontLeftDrive, leftSpeed * atan(0.1 * abs(angle - gyroValue)), true);
		setSpeed(frontRightDrive, rightSpeed * atan(0.1 * abs(angle - gyroValue)), true);

	}

	leftSpeed = rightTurn ? -128: 128;
	rightSpeed = rightTurn ? 128: -128;

	setSpeed(frontLeftDrive, leftSpeed, true);
	setSpeed(frontRightDrive, rightSpeed, true);

	delay(100);

	setAllDrive(0);
}



/*
	angle > 0 >>> raise
	angle < 0 >>> lower

	Status:
	- testing required

	Issues/Ideas:
	-
*/
void moveDRFB(float angle) {
	int initialVal = nMotorEncoder[drfb1];
	float speed = angle < 0 ? -128 : 128;
	while(abs(initialVal - nMotorEncoder[drfb1]) < abs(angle))
		setSpeed(drfb1, speed, true);
	setSpeed(drfb1, 0, true);
}
