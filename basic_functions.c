#pragma systemFile //supress unreferenced function warning

//variables & constants
const float WHEEL_DIAMETER = 3.25;
float gyroValue;


void setAllDrive(int speed) {
	setSpeed(leftDrive1, speed);
	setSpeed(rightDrive1, speed);
}

/*
	distance > 0 >>> forward
	distance < 0 >>> backward
*/
void driveInches(float distance) {



	const float max = distance < 0 ? -80 : 80;
	const float ticks = abs(distance / (WHEEL_DIAMETER * PI) * 392); //will always be positive

	float leftTicks = 0;
	float rightTicks = 0;
	float average = 0;
	float speed = 0;
	float leftSpeed = 0;
	float rightSpeed = 0;

	while(leftTicks < ticks || rightTicks < ticks) {

		leftTicks = abs(SensorValue[leftEncoder]);
		rightTicks = abs(SensorValue[rightEncoder]);
		average = ( leftTicks + rightTicks ) / 2.0;

		speed = max;//atan(0.05*(ticks - average)) / (PI/2) * max;

		if(leftTicks < rightTicks) {
			leftSpeed = speed;
			rightSpeed = speed - atan(0.5 *(average-leftTicks)) / (PI/2) * speed;
		} else {
			leftSpeed = speed - atan(0.5 *(average-rightTicks)) / (PI/2) * speed;
			rightSpeed = speed;
		}

		setSpeed(leftDrive1, leftSpeed);
		setSpeed(rightDrive1, rightSpeed);

	}

  setAllDrive(0);

}

void squareRobot() {
	while(!SensorValue[leftTouch] || !SensorValue[rightTouch]) {
		if(SensorValue[leftTouch])
			setSpeed(leftDrive1, 0);
		if(SensorValue[rightTouch])
			setSpeed(rightDrive1, 0);
	}
	setAllDrive(0);
}

/*
	angle > 0 >>> clockwise
	angle < 0 >>> counterclockwise
*/
void turnDegrees(float angle){

	bool rightTurn = angle > 0;

	float initial = abs(SensorValue[in1]/10.0);
	float absGyroValue = abs(SensorValue[in1]/10.0);

	float leftSpeed = rightTurn ? 80 : -80;
	float rightSpeed = rightTurn ? -80 : 80;

	const float K = 0.04;

	while(abs(absGyroValue-initial) < abs(angle) ) {
		setSpeed(leftDrive1, leftSpeed * atan(K * abs(angle - gyroValue)));
		setSpeed(rightDrive1, rightSpeed * atan(K * abs(angle - gyroValue)));
		absGyroValue = abs(SensorValue[in1]/10.0);
	}

	leftSpeed = rightTurn ? -128: 128;
	rightSpeed = rightTurn ? 128: -128;

	setSpeed(leftDrive1, leftSpeed);
	setSpeed(rightDrive1, rightSpeed);

	delay(100);

	setAllDrive(0);
}

/*
	angle > 0 >>> clockwise
	angle < 0 >>> counterclockwise
*/
//Try to avoid using this function, it will eventually malfunction because of gyro drift
void targetAngle(float angle, bool rightTurn){

	const float speed = rightTurn ? -80 : 80;

	float leftSpeed = -speed;
	float rightSpeed = speed;

	while( gyroValue < angle - 0.5 || gyroValue > angle + 0.5) {

		gyroValue = SensorValue[in1] / 10.0;
		if(gyroValue < 0)
			gyroValue = 360 + gyroValue;
		//gyroValue = gyroValue < 0 ? 360 - gyroValue : gyroValue;

		setSpeed(leftDrive1, leftSpeed * atan(0.1 * abs(angle - gyroValue)));
		setSpeed(rightDrive1, rightSpeed * atan(0.1 * abs(angle - gyroValue)));

	}

	leftSpeed = rightTurn ? -128: 128;
	rightSpeed = rightTurn ? 128: -128;

	setSpeed(leftDrive1, leftSpeed);
	setSpeed(rightDrive1, rightSpeed);

	delay(100);

	setAllDrive(0);
}

/*
	angle > 0 >>> raise
	angle < 0 >>> lower
*/
//Don't use this function, it wastes time, use a task in parallel instead
void moveDRFB(float angle) {
	int initialVal = nMotorEncoder[drfb1];
	float speed = angle < 0 ? -128 : 128;
	while(abs(initialVal - nMotorEncoder[drfb1]) < abs(angle))
		setSpeed(drfb1, speed);
	setSpeed(drfb1, 0);
}
