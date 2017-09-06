#include "main.h"

int maxSpeed = 127;

void operatorControl() {

	enable(); //enable slew control

	while (1) {

		//Primary Controller

		//Change drive speed
		if( joystickGetDigital(1, 8, JOY_UP) ) {
			maxSpeed = 127;
		} else if( joystickGetDigital(1, 8, JOY_LEFT) || joystickGetDigital(1, 8, JOY_RIGHT) ) {
			maxSpeed = 64;
		} else {
			maxSpeed = 32;
		}

		//Drive control
		setLeftDrive( joystickGetAnalog(1, 3) * maxSpeed / 127.0 , false);
		setRightDrive( joystickGetAnalog(1, 2) * maxSpeed / 127.0 , false);

		//DRFB control
		if( joystickGetDigital(1, 5, JOY_UP) ) { //If button 5U is pressed
			setMobileGoalLift(127, false);
		} else if( joystickGetDigital(1, 5, JOY_DOWN) ) { //If button 5D is pressed
			 setMobileGoalLift(-127, false);
		} else {
			setMobileGoalLift(0, false);
		}

		//Mobile Goal Lift control
		if( joystickGetDigital(1, 6, JOY_UP) ) { //If button 6U is pressed
			setDRFB(127, false);
		} else if( joystickGetDigital(1, 6, JOY_DOWN) ) { //If button 6D is pressed
			 setDRFB(-127, false);
		} else {
			setDRFB(0, false);
		}



		//Secondary Controller

		//Jaw Control
		if( joystickGetDigital(2, 5, JOY_UP) ) {
			setJaw(127, false);
		} else if( joystickGetDigital(2, 5, JOY_DOWN) ) {
			 setJaw(-127, false);
		} else {
			setJaw(0, false);
		}

		//Claw Control
		if( joystickGetDigital(2, 6, JOY_UP) ) {
			setClaw(127, false);
		} else if( joystickGetDigital(2, 6, JOY_DOWN) ) {
			 setClaw(-127, false);
		} else {
			setClaw(0, false);
		}


		delay(20);

	}
}
