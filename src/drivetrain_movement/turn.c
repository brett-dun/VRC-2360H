#include "drivetrain_movement.h"

void turn(float degrees) {

  bool rightTurn = degrees > 0;

  gyroReset(gyro);
	float absGyroValue = abs(gyroGet(gyro));

	const float speed = 127;
	float leftSpeed = rightTurn ? speed : -speed;
	float rightSpeed = -leftSpeed;

	//const float K = 0.05; //Not using this right now
	while(absGyroValue < abs(degrees) ) {
    setDrive(leftSpeed, rightSpeed);
		absGyroValue = abs(gyroGet(gyro));
	}

  setDrive(rightTurn ? -127: 127, rightTurn ? 127: -127);
	delay(100);
	setDrive(0,0);

}
