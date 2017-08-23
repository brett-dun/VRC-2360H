#ifndef ROBOTPROPERTIES_H_
#define ROBOTPROPERTIES_H_

#include <API.h>
#include "constants.h"
#include "slew_rate.h"

//Motors
#define FRONT_RIGHT_DRIVE SLEW_MOTOR_1
#define FRONT_LEFT_DRIVE SLEW_MOTOR_2
#define MGL_LEFT SLEW_MOTOR_3

//Digital Sensors
#define LEFT_TOUCH DGTL_1
#define RIGHT_TOUCH DGTL_2

//Analog Sensors

//Gyro
Gyro gyro;

//Robot Specific Constants
const float WHEEL_DIAMETER = 4.0; //Wheel diameter in inches
const float DRIVETRAIN_GR = 0.5; //Drivetrain gear ratio (Tout / Tin)
const float DRIVE_TICKS = 627.2; //High Torque - 392 for High Speed



#endif
