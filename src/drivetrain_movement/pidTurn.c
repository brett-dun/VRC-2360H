#include "drivetrain_movement.h"

void pidTurn(float degrees) {
  const float KP = 1.3;
	const float KI = 0.1;
	const float KD = 0.1;

	float output = 0;
	float error = 0;
	float prevError = 0;
	float proportion = 0;
	float integral = 0;
	float derivative = 0;

	while(true) {

		float absGyroValue = abs(gyroGet(gyro));

		error = abs(degrees) - absGyroValue;

		proportion = error * KP;
		integral = error == 0 ? 0 : (integral > 50.0/KI ? 50.0/KI : integral+prevError*KI);
		derivative = (error - prevError) * KD;

		output = proportion + integral + derivative;

    if(error < 1.0) {
			setDrive(0, 0);
			return;
		}

		setDrive(degrees > 0 ? output: -output, degrees > 0 ? -output : output);

	}

}
