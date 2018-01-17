
typedef struct {
	float KP;
	float KI;
	float KD;

	float output;

	float error;
	float prevError;

	float proportion;
	float integral;
	float derivative;

} PIDController;


#define PID_LOOPS 2
PIDController pid[PID_LOOPS];

//double reverse four bar
pid[0].KP = 1.3;
pid[0].KI = 0.;
pid[0].KD = 0.;

//chain bar
pid[1].KP = 1.3;
pid[1].KI = 0.;
pid[1].KD = 0.;


task pidTask() {

	while(true) {

		for(int i = 0; i < PID_LOOPS; i++) {

			pid[i].prevError = pid[i].error; //Set the current error to the previous error

			switch(i) {
				case 0: pid[i].error = 0;
				case 1: pid[i].error = 0;
			}

			pid[i].proportion = pid[i].error * pid[i].KP; //Calculate the proportion
			pid[i].integral += pid[i].prevError * pid[i].KI;
			pid[i].derivative = (pid[i].error - pid[i].prevError) * pid[i].KD; //Calculate the derivative

			pid[i].output = pid[i].proportion + pid[i].integral + pid[i].derivative; //Calculate the output
			pid[i].output = pid[i].output > 127 ? 127 : (pid[i].output < -127 ? -127 : pid[i].output);

		}

		setSpeed(rightDRFB, pid[0].output, true);
		setSpeed(chainBar, pid[1].output, true);

		delay(20); //Wait for 20 ms

	}
}
