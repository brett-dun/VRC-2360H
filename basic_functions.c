#pragma systemFile //supress unreferenced function warning

const float WHEEL_DIAMETER = 4;
//float sixBarTarget = -40; //starting position
float gyroValue;

/*
	distance > 0 >>> forward
	distance < 0 >>> backward
*/
void driveInches(float distance) {

	nMotorEncoder[backLeft] = 0;
	nMotorEncoder[frontLeft] = 0;
	nMotorEncoder[backRight] = 0;
	nMotorEncoder[frontRight] = 0;

	const float max = distance < 0 ? -128 : 128;
	const float ticks = abs(distance / (WHEEL_DIAMETER * PI) * 392); //will always be positive

	float leftAverage = 0;
	float rightAverage = 0;
	float average = 0;
	float speed = 0;
	float leftSpeed = 0;
	float rightSpeed = 0;

	do {

		leftAverage = ( abs(nMotorEncoder[backLeft]) + abs(nMotorEncoder[frontLeft]) ) / 2.0;
		rightAverage = ( abs(nMotorEncoder[backRight]) + abs(nMotorEncoder[frontRight]) ) / 2.0;
		average = ( leftAverage + rightAverage ) / 2.0;

		speed = max;//atan(0.00125*3*(ticks - average)) / (PI/2) * max;

		if(leftAverage < rightAverage) {
			leftSpeed = speed;
			rightSpeed = speed - atan(0.5 *(average-leftAverage)) / (PI/2) * speed;
		} else {
			leftSpeed = speed - atan(0.5 *(average-rightAverage)) / (PI/2) * speed;
			rightSpeed = speed;
		}

		motor[backLeft] = leftSpeed;
		motor[frontLeft] = leftSpeed;
		motor[backRight] = rightSpeed;
		motor[frontRight] = rightSpeed;

	} while(leftAverage < ticks || rightAverage < ticks);


	motor[backLeft] = max < 0 ? 128: -128;
	motor[frontLeft] = max < 0 ? 128: -128;
	motor[backRight] = max < 0 ? 128: -128;
	motor[frontRight] = max < 0 ? 128: -128;

	delay(100);

  motor[backLeft] = 0;
	motor[frontLeft] = 0;
	motor[backRight] = 0;
	motor[frontRight] = 0;

}

void squareRobot() {

	do {
		motor[backLeft] = -128;
		motor[frontLeft] = -128;
		motor[backRight] = -128;
		motor[frontRight] = -128;
	} while(!SensorValue[touch1] || !SensorValue[touch2]);

	motor[backLeft] = 0;
	motor[frontLeft] = 0;
	motor[backRight] = 0;
	motor[frontRight] = 0;

}


/*
	angle > 0 >>> clockwise
	angle < 0 >>> counterclockwise
*/

void turnDegrees(float angle){

	bool rightTurn = angle < 0;

	float initial = abs(SensorValue[in1]);
	float absGyroValue = abs(SensorValue[in1]/10.0);

	float leftSpeed = rightTurn ? 80 : -80;
	float rightSpeed = rightTurn ? -80 : 80;

	do {
		motor[backLeft] = leftSpeed * atan(0.1 * abs(angle - gyroValue));
		motor[frontLeft] = leftSpeed * atan(0.1 * abs(angle - gyroValue));
		motor[backRight] = rightSpeed * atan(0.1 * abs(angle - gyroValue));
		motor[frontRight] = rightSpeed * atan(0.1 * abs(angle - gyroValue));
		absGyroValue = abs(SensorValue[in1]/10.0);
	} while(abs(absGyroValue-initial) < abs(angle) );



	motor[backLeft] = rightTurn ? -128: 128;
	motor[frontLeft] = rightTurn ? -128: 128;
	motor[backRight] = rightTurn ? 128: -128;
	motor[frontRight] = rightTurn ? 128: -128;

	delay(100);

	motor[backLeft] = 0;
	motor[frontLeft] = 0;
	motor[backRight] = 0;
	motor[frontRight] = 0;


}

/*
	angle > 0 >>> clockwise
	angle < 0 >>> counterclockwise
*/
void targetAngle(float angle, bool rightTurn){

	const float speed = rightTurn ? -80 : 80;

	float leftSpeed = -speed;
	float rightSpeed = speed;

	do {

		gyroValue = SensorValue[in1] / 10.0;
		if(gyroValue < 0)
			gyroValue = 360 + gyroValue;
		//gyroValue = gyroValue < 0 ? 360 - gyroValue : gyroValue;

		motor[backLeft] = leftSpeed * atan(0.1 * abs(angle - gyroValue));
		motor[frontLeft] = leftSpeed * atan(0.1 * abs(angle - gyroValue));
		motor[backRight] = rightSpeed * atan(0.1 * abs(angle - gyroValue));
		motor[frontRight] = rightSpeed * atan(0.1 * abs(angle - gyroValue));

	} while( gyroValue < angle - 0.5 || gyroValue > angle + 0.5);


	motor[backLeft] = rightTurn ? -128: 128;
	motor[frontLeft] = rightTurn ? -128: 128;
	motor[backRight] = rightTurn ? 128: -128;
	motor[frontRight] = rightTurn ? 128: -128;

	delay(100);

	motor[backLeft] = 0;
	motor[frontLeft] = 0;
	motor[backRight] = 0;
	motor[frontRight] = 0;
}


/*
	angle > 0 >>> raise
	angle < 0 >>> lower
*/
void moveForkliftDegrees(float angle) {

	SensorValue[sixBar] = 0;
	float speed = angle < 0 ? -128 : 128;

	do {
		motor[forklift1] = speed;
		motor[forklift2] = speed;
		motor[forklift3] = speed;
		motor[forklift4] = speed;
		motor[forklift5] = speed;

	} while(abs(SensorValue[sixBar]) < abs(angle));

	motor[forklift1] = 0;
	motor[forklift2] = 0;
	motor[forklift3] = 0;
	motor[forklift4] = 0;
	motor[forklift5] = 0;

}

task raiseForklift() {

	//float initial = abs(SensorValue[sixBar]);

	do {
		motor[forklift1] = 128;
		motor[forklift2] = 128;
		motor[forklift3] = 128;
		motor[forklift4] = 128;
		motor[forklift5] = 128;

	} while(abs(SensorValue[sixBar]) < 100);

	motor[forklift1] = 0;
	motor[forklift2] = 0;
	motor[forklift3] = 0;
	motor[forklift4] = 0;
	motor[forklift5] = 0;
}

task lowerForklift() {
	//SensorValue[sixBar] = 0;

	//float initial = abs(SensorValue[sixBar]);

	do {

		motor[forklift1] = -128;
		motor[forklift2] = -128;
		motor[forklift3] = -128;
		motor[forklift4] = -128;
		motor[forklift5] = -128;

	} while(abs(SensorValue[sixBar]) > 1);

	motor[forklift1] = 0;
	motor[forklift2] = 0;
	motor[forklift3] = 0;
	motor[forklift4] = 0;
	motor[forklift5] = 0;
}

task maintainForkliftUp() {
	motor[forklift1] = 128;
	motor[forklift2] = 128;
	motor[forklift3] = 128;
	motor[forklift4] = 128;
	motor[forklift5] = 128;
	delay(500);
	motor[forklift1] = 0;
	motor[forklift2] = 0;
	motor[forklift3] = 0;
	motor[forklift4] = 0;
	motor[forklift5] = 0;
}

task maintainForkliftDown() {
	motor[forklift1] = -60;
	motor[forklift2] = -60;
	motor[forklift3] = -60;
	motor[forklift4] = -60;
	motor[forklift5] = -60;
	delay(1500);
	motor[forklift1] = 0;
	motor[forklift2] = 0;
	motor[forklift3] = 0;
	motor[forklift4] = 0;
	motor[forklift5] = 0;
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

/*void changeClaw() {
	SensorValue[claw] = !SensorValue[claw];
}*/
