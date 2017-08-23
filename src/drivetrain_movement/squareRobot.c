#include "drivetrain_movement.h"

void squareRobot() {

  while(!digitalRead(LEFT_TOUCH) || !digitalRead(LEFT_TOUCH)) {

		if(digitalRead(LEFT_TOUCH))
			setLeftDrive(0,true);
		else
			setLeftDrive(-127,true);

		if(digitalRead(RIGHT_TOUCH))
			setRightDrive(0,true);
		else
			setRightDrive(-127,true);

	}

	setDrive(0,0);

}
