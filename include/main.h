#ifndef MAIN_H_
#define MAIN_H_

#include <API.h>
#include <smart_motor.h>

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
