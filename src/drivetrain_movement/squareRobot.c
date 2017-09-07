#include "drivetrain_movement.h"

void squareRobot() {

  while(!digitalRead(L_BACK_TOUCH) || !digitalRead(R_BACK_TOUCH)) {

		if(digitalRead(L_BACK_TOUCH))
			setLeftDrive(0,true);
		else
			setLeftDrive(-127,true);

		if(digitalRead(R_BACK_TOUCH))
			setRightDrive(0,true);
		else
			setRightDrive(-127,true);

	}

	setDrive(0,0);

}
