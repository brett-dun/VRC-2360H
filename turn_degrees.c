#pragma systemFile //This prevents "Unreference variable" and "Unreferenced function" warnings

void turnDegrees(float angle, int sharp = 0) {
	//this should be rewritten at some point

	bool rightTurn = angle > 0;

	float previous = SensorValue[in1] / 10.0; //previous gyroscope value
	float current = SensorValue[in1] / 10.0; //current gyroscope value
	float sum = 0; //sum of the changes of the gyroscope values
	float angleDifference = angle; //how much the robot still needs to turn

	const float speed = 45; //speed multiplier
	float leftSpeed = rightTurn ? speed : -speed; //set speed positive or negative
	float rightSpeed = -leftSpeed; //set speed positive or negative

	float leftPower; //power to be sent to the left
	float rightPower; //power to be sent to the right

	const float K = 0.1; //constant for arctangent function

	while( fabs(sum) < fabs(angle) ) { //while the change in the gyroscopes value is less than the desired turn angle

		previous = current; //set the current value to the previous value
		current = SensorValue[in1] / 10.0; //store the gyroscopes current value
		if( fabs(current - previous) < 180 ) //if the gyroscope did not roll over
			sum += fabs(current - previous); //add the change in the gyroscopes value to the sum

		angleDifference = fabs(angle) - fabs(sum); //calculate the difference between the desired angle and the target angle

		float power = atan(K * fabs(angleDifference)); //power multiplier to be sent to the motors

		setSpeedImmediate(leftDrive, fabs(power) < 0.33 && sharp ? leftSpeed / 3.0 : leftSpeed * power);
		setSpeedImmediate(rightDrive, fabs(power) < 0.33 && sharp ? rightSpeed / 3.0 : rightSpeed * power);

	}

	setDrive(0);
}
