#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, dgtl1,  ,               sensorQuadEncoder)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           one,           tmotorVex393_HBridge, openLoop, encoderPort, I2C_1)
#pragma config(Motor,  port2,           two,           tmotorVex393_MC29, openLoop, encoderPort, I2C_1)
#pragma config(Motor,  port10,          ten,           tmotorVex393_HBridge, openLoop, encoderPort, I2C_1)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "smart_motor.c"

float s1, s10,r;
int i;

task t {
	while(1) {

	}
}

task main() {

	init();

	startTask(t);

	setSpeed(one, 0, true);
	i = getPointer(one) == &motors[0];

	setSpeed(ten, 127, true);

	clearTimer(T1);
	while(time1[T1] < 5000) {
		s1 = motors[0].currentSpeed;
		s10 = motors[9].currentSpeed;
		r = motors[0].rpm;
		delay(20);
	}
}
