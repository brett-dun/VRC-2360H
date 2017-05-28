#pragma systemFile //supress unreferenced function warning

//variables & constants
const float WHEEL_DIAMETER = 3.25;
float gyroValue;


void setAllDrive(int speed) {
	setSpeed(backLeft, speed);
	setSpeed(frontLeft, speed);
	setSpeed(backRight, speed);
	setSpeed(frontRight, speed);
}

/*
	distance > 0 >>> forward
	distance < 0 >>> backward
*/
void driveInches(float distance) {

	nMotorEncoder[backLeft] = 0;
	nMotorEncoder[frontLeft] = 0;
	nMotorEncoder[backRight] = 0;
	nMotorEncoder[frontRight] = 0;

	const float max = distance < 0 ? -80 : 80;
	const float ticks = abs(distance / (WHEEL_DIAMETER * PI) * 392); //will always be positive

	float leftAverage = 0;
	float rightAverage = 0;
	float average = 0;
	float speed = 0;
	float leftSpeed = 0;
	float rightSpeed = 0;

	while(leftAverage < ticks || rightAverage < ticks) {

		leftAverage = abs(nMotorEncoder[frontLeft]);
		rightAverage = abs(nMotorEncoder[frontRight]);
		average = ( leftAverage + rightAverage ) / 2.0;

		speed = max;//atan(0.05*(ticks - average)) / (PI/2) * max;

		if(leftAverage < rightAverage) {
			leftSpeed = speed;
			rightSpeed = speed - atan(0.5 *(average-leftAverage)) / (PI/2) * speed;
		} else {
			leftSpeed = speed - atan(0.5 *(average-rightAverage)) / (PI/2) * speed;
			rightSpeed = speed;
		}

		setSpeed(backLeft, leftSpeed);
		setSpeed(frontLeft, leftSpeed);
		setSpeed(backRight, rightSpeed);
		setSpeed(frontRight, rightSpeed);

	}

	/*leftSpeed = max < 0 ? 127: -127;
	rightSpeed = max < 0 ? 127: -127;

	setMotor(backLeft, leftSpeed);
	setMotor(frontLeft, leftSpeed);
	setMotor(backRight, rightSpeed);
	setMotor(frontRight, rightSpeed);*/

	/*float prevLeftside = (abs(nMotorEncoder(backLeft)) + abs(nMotorEncoder(frontLeft)) ) / 2.0;
	float prevRightside = (abs(nMotorEncoder(backRight)) + abs(nMotorEncoder(frontRight)) ) / 2.0;
	delay(10);
	float currentLeftside = (abs(nMotorEncoder(backLeft)) + abs(nMotorEncoder(frontLeft)) ) / 2.0;
	float currentRightside = (abs(nMotorEncoder(backRight)) + abs(nMotorEncoder(frontRight)) ) / 2.0;

	while(abs(prevLeftside - currentLeftside) < 5 || abs(prevRightside - currentRightside) < 5) {
		if(abs(prevLeftside - currentLeftside) < 2) {
			setMotor(backLeft, 0);
			setMotor(frontLeft, 0);
		}
		if(abs(prevRightside - currentRightside) < 2) {
			setMotor(backRight, 0);
			setMotor(frontRight, 0);
		}
		prevLeftside = currentLeftside;
		prevRightside = currentRightside;
		currentLeftside = (abs(nMotorEncoder(backLeft)) + abs(nMotorEncoder(frontLeft)) ) / 2.0;
		currentRightside = (abs(nMotorEncoder(backRight)) + abs(nMotorEncoder(frontRight)) ) / 2.0;
		delay(10);
	}*/
	//delay(100);
	while(leftAverage > ticks || rightAverage > ticks) {

		leftAverage = abs(nMotorEncoder[frontLeft]);
		rightAverage = abs(nMotorEncoder[frontRight]);
		average = ( leftAverage + rightAverage ) / 2.0;

		speed = atan(0.05*(ticks - average)) / (PI/2.0) * max * 0.5;

		if(leftAverage > rightAverage) {
			leftSpeed = speed;
			rightSpeed = speed - atan(0.5 *(average-leftAverage)) / (PI/2) * speed;
		} else {
			leftSpeed = speed - atan(0.5 *(average-rightAverage)) / (PI/2) * speed;
			rightSpeed = speed;
		}

		setSpeed(backLeft, leftSpeed);
		setSpeed(frontLeft, leftSpeed);
		setSpeed(backRight, rightSpeed);
		setSpeed(frontRight, rightSpeed);

	}

  setAllDrive(0);

}

void squareRobot() {
	while(!SensorValue[touch1] || !SensorValue[touch2])
		setAllDrive(-128);
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
		setSpeed(backLeft, leftSpeed * atan(K * abs(angle - gyroValue)));
		setSpeed(frontLeft, leftSpeed * atan(K * abs(angle - gyroValue)));
		setSpeed(backRight, rightSpeed * atan(K * abs(angle - gyroValue)));
		setSpeed(frontRight, rightSpeed * atan(K * abs(angle - gyroValue)));
		absGyroValue = abs(SensorValue[in1]/10.0);
	}

	leftSpeed = rightTurn ? -128: 128;
	rightSpeed = rightTurn ? 128: -128;

	setSpeed(backLeft, leftSpeed);
	setSpeed(frontLeft, leftSpeed);
	setSpeed(backRight, rightSpeed);
	setSpeed(frontRight, rightSpeed);

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

		setSpeed(backLeft, leftSpeed * atan(0.1 * abs(angle - gyroValue)));
		setSpeed(frontLeft, leftSpeed * atan(0.1 * abs(angle - gyroValue)));
		setSpeed(backRight, rightSpeed * atan(0.1 * abs(angle - gyroValue)));
		setSpeed(frontRight, rightSpeed * atan(0.1 * abs(angle - gyroValue)));

	}

	leftSpeed = rightTurn ? -128: 128;
	rightSpeed = rightTurn ? 128: -128;

	setSpeed(backLeft, leftSpeed);
	setSpeed(frontLeft, leftSpeed);
	setSpeed(backRight, rightSpeed);
	setSpeed(frontRight, rightSpeed);

	delay(100);

	setAllDrive(0);
}




void setAllForklift(int speed) {
	setSpeed(forklift1, speed);
	setSpeed(forklift2, speed);
	setSpeed(forklift3, speed);
	setSpeed(forklift4, speed);
	setSpeed(forklift5, speed);
}

/*
	angle > 0 >>> raise
	angle < 0 >>> lower
*/
//Don't use this function, it wastes time, use a task in parallel instead
void moveForkliftDegrees(float angle) {
	SensorValue[sixBar] = 0;
	float speed = angle < 0 ? -128 : 128;
	while(abs(SensorValue[sixBar]) < abs(angle))
		setAllForklift(speed);
	setAllForklift(0);
}

task raiseForklift() {
	while(abs(SensorValue[sixBar]) < 100)
		setAllForklift(128);
	setAllForklift(0);
}

task lowerForklift() {
	while(abs(SensorValue[sixBar]) > 1)
		setAllForklift(-128);
	setAllForklift(0);
}

task maintainForkliftUp() {
	setAllForklift(128);
	delay(500);
	setAllForklift(0);
}

task maintainForkliftDown() {
	setAllForklift(-60);
	delay(1500);
	setAllForklift(0);
}




/*
Use these methods to avoid having to change the sensor value if the physical setup of the pneumatics changes
*/
void openClaw() {
	SensorValue[claw] = 1;
}
void closeClaw() {
	SensorValue[claw] = 0;
}
