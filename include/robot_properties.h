#ifndef ROBOTPROPERTIES_H_
#define ROBOTPROPERTIES_H_

#include <API.h>
#include "constants.h"
#include "slew_rate.h"

//Motorsn- we need to decide port setup
#define L_DRIVE SLEW_MOTOR_2
#define L_MIDDLE_DRIVE SLEW_MOTOR_4
//#define L_BACK_DRIVE SLEW_MOTOR_4//two motors here, one to power expander
#define R_DRIVE SLEW_MOTOR_9
#define R_MIDDLE_DRIVE SLEW_MOTOR_7
//#define R_BACK_DRIVE SLEW_MOTOR_7 //two motors here, one to power expander
#define L_DRFB SLEW_MOTOR_3
#define R_DRFB SLEW_MOTOR_8
#define CB SLEW_MOTOR_5
#define CLAW SLEW_MOTOR_6

//Digital Sensors
#define L_BACK_TOUCH DGTL_4
#define R_BACK_TOUCH DGTL_1
#define L_DRFB_TOUCH DGTL_3
#define R_DRFB_TOUCH DGTL_2
#define PNEUMATICS DGTL_5
#define CLAW_TOUCH DGTL_6

//Analog Sensors

//Gyro - gyro is different from other analog sensors
Gyro gyro;

//Robot Specific Constants
#define WHEEL_DIAMETER 4.0 //Wheel diameter in inches
#define DRIVETRAIN_GR 0.5 //Drivetrain gear ratio (Tout / Tin)
#define DRIVE_TICKS 627.2 //High Torque - 392 for High Speed



#endif
