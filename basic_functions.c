#pragma systemFile //This prevents "Unreference variable" and "Unreferenced function" warnings

float gyroValue; //value of the gyroscope


/*
	Status:
	- working

	Issues/Ideas:
	-
*/
void setAllDrive(int speed) {
	setSpeed(leftDrive, speed, true);
	setSpeed(rightDrive, speed, true);
}


/*
	Status:
	- working

	Issues/Ideas:
	-
*/
void setDrive(float leftSpeed, float rightSpeed) {
	setSpeed(leftDrive, leftSpeed, true);
	setSpeed(rightDrive, rightSpeed, true);
}


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
			setSpeed(leftDrive, speed, true);
			setSpeed(rightDrive, speed - atan(0.1 *(average-leftTicks)) / (PI/2) * speed, true);
		} else {
			setSpeed(leftDrive, speed - atan(0.1 *(average-rightTicks)) / (PI/2) * speed, true);
			setSpeed(rightDrive, speed, true);
		}

	}

  setAllDrive(max < 0 ? 127 : -127);
  delay(100);
  setAllDrive(0);

}


/*
	Status:
	- testing required

	Issues/Ideas:
	-
*/
void squareRobot() {
	while(!SensorValue[leftBump] || !SensorValue[rightBump]) {

		if(SensorValue[leftBump])
			setSpeed(leftDrive, 0, true);
		else
			setSpeed(leftDrive, -127, true);

		if(SensorValue[rightBump])
			setSpeed(rightDrive, 0, true);
		else
			setSpeed(rightDrive, -127, true);

	}
	setAllDrive(0);
}



/*
	angle > 0 >>> clockwise
	angle < 0 >>> counterclockwise

	Status:
	- working

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

	while(fabs(absGyroValue-initial) < abs(angle) ) {
		setSpeed(leftDrive, leftSpeed * atan(K * fabs(angle - gyroValue)), true);
		setSpeed(rightDrive, rightSpeed * atan(K * fabs(angle - gyroValue)), true);
		absGyroValue = fabs(SensorValue[in1]/10.0);
	}

	setSpeed(leftDrive, rightTurn ? -127: 127, true);
	setSpeed(rightDrive, rightTurn ? 127: -127, true);

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
	int initialVal = nMotorEncoder[leftDRFB];
	float speed = angle < 0 ? -128 : 128; //set s
	while(abs(initialVal - nMotorEncoder[leftDRFB]) < abs(angle)) //while it has not moved the specified angle
		setSpeed(leftDRFB, speed, true); //set the double reverse four bar to the speed
	setSpeed(leftDRFB, 0, true); //stop the double reverse four bar
}


/*
	Status:
	- working

	Issues/Ideas:
	- claw doesn't always open until it hits the limit switch
*/
void openClaw(int time) {
	clearTimer(T1);
	while(time1[T1] < time) {
		if(!SensorValue[clawButton])
			setSpeed(intake, 64, true);
		else
			setSpeed(intake, 32, true);
	}
	setSpeed(intake, 0, true);
}


/*
	Status:
	- working

	Issues/Ideas:
	-
*/
void raiseMobileGoal() {
	SensorValue[mobileGoalLift] = 0;
}


/*
	Status:
	- working

	Issues/Ideas:
	-
*/
void lowerMobileGoal() {
	SensorValue[mobileGoalLift] = 1;
}
