#include "drivetrain_movement.h"

void drive(float inches) {

  const float max = inches < 0 ? -80 : 80;
  const float ticks = inches * 360; //* DRIVETRAIN_GR * DRIVE_TICKS / (WHEEL_DIAMETER * PI); //ticks needed to go the desired distance

  int left = 0;
	int right = 0;
	float average = 0;
	float speed = 0;

  //imeDriveReset();

  while(left < ticks || right < ticks) {

		//imeDriveGet(&left, &right);
		average = ( left + right ) / 2.0;

		speed = max;//atan(0.05*(ticks - average)) / (PI/2) * max;

    const float K = 0.5;
		if(left < right)
      setDrive(speed, speed - atan( K*(average-left) ) / (PI/2) * speed);
		else
      setDrive(speed - atan( K*(average-right) ) / (PI/2) * speed, speed);

	}

  setDrive(0,0);

}
