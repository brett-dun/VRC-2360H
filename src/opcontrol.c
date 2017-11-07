/** @file opcontrol.c
 * @brief File for operator control code
 *
 * This file should contain the user operatorControl() function and any functions related to it.
 *
 * Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"

/*
 * Runs the user operator control code. This function will be started in its own task with the
 * default priority and stack size whenever the robot is enabled via the Field Management System
 * or the VEX Competition Switch in the operator control mode. If the robot is disabled or
 * communications is lost, the operator control task will be stopped by the kernel. Re-enabling
 * the robot will restart the task, not resume it from where it left off.
 *
 * If no VEX Competition Switch or Field Management system is plugged in, the VEX Cortex will
 * run the operator control task. Be warned that this will also occur if the VEX Cortex is
 * tethered directly to a computer via the USB A to A cable without any VEX Joystick attached.
 *
 * Code running in this task can take almost any action, as the VEX Joystick is available and
 * the scheduler is operational. However, proper use of delay() or taskDelayUntil() is highly
 * recommended to give other tasks (including system tasks such as updating LCDs) time to run.
 *
 * This task should never exit; it should end with some kind of infinite loop, even if empty.
 */
void operatorControl() {

	enableSlewControl();

	int left = 0;
	int right = 0;

	imeGet(3, &right);
	imeGet(4, &left);


	while (1) {


		setSpeed(L_DRIVE, -joystickGetAnalog(1, 3), false);
		setSpeed(L_MIDDLE_DRIVE, joystickGetAnalog(1, 3), false);
		setSpeed(R_DRIVE, joystickGetAnalog(1, 2), false);
		setSpeed(R_MIDDLE_DRIVE, -joystickGetAnalog(1, 2), false);


		if(joystickGetDigital(1, 5, JOY_UP)) {
			digitalWrite(5, true);
		} else if(joystickGetDigital(1, 5, JOY_DOWN)) {
			digitalWrite(5, false);
		}


		if(joystickGetDigital(1, 6, JOY_UP)) {
			setSpeed(L_DRFB, 127, false);
			setSpeed(R_DRFB, 127, false);
		} else if(joystickGetDigital(1, 6, JOY_DOWN)) {
			setSpeed(L_DRFB, -127, false);
			setSpeed(R_DRFB, -127, false);
		} else {
			setSpeed(L_DRFB, 0, false);
			setSpeed(R_DRFB, 0, false);
		}


		if(joystickGetDigital(1, 5, JOY_UP)) {
			setSpeed(CB, 127, false);
		} else if(joystickGetDigital(1, 5, JOY_DOWN)) {
			setSpeed(CB, -127, false);
		} else {
			setSpeed(CB, 0, false);
		}


		if(joystickGetDigital(1, 6, JOY_UP) || joystickGetDigital(1, 6, JOY_DOWN)) {
			if(digitalRead(CLAW_TOUCH)) {
				setSpeed(CLAW, -16, false);
			} else {
				setSpeed(CLAW, -127, false);
			}
		} else {
			setSpeed(CLAW, 0, false);
		}


		if(digitalRead(L_DRFB_TOUCH) && digitalRead(R_DRFB)) {
			imeReset(3); //left
			imeReset(4); //right
		}


		delay(20);


	}
}
