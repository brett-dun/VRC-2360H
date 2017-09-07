#ifndef MAIN_H_
#define MAIN_H_

#include <API.h>

#include "slew_rate.h"
#include "constants.h"

#include "robot_properties.h"

//Including both of these header files causes redefintions of most variables -- Fix asap
#include "drivetrain_movement.h"
#include "movement.h"

#include "led_control.h"


#ifdef __cplusplus
extern "C" {
#endif



void autonomous();

void initializeIO();

void initialize();

void operatorControl();




#ifdef __cplusplus
}
#endif

#endif
