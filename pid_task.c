
typedef struct {

	float KP;
	float KI;
	float KD;

	float target;

	float output;

	float error;
	float prevError;

	float proportion;
	float integral;
	float derivative;

} PIDController;

PIDController drfb;
PIDController cb;

void setDRFBAngle(float angle) {
	drfb.target = angle;
}

void setCBAngle(float angle) {
	cb.target = angle;
}

task pidTask() {

	nMotorEncoder[rightDRFB] = 0;
	nMotorEncoder[chainBar] = 0;

	//double reverse four bar
	drfb.KP = 10.;
	drfb.KI = 0.1;
	drfb.KD = 1.;

	//chain bar
	cb.KP = 1.3;
	cb.KI = 0.;
	cb.KD = 0.;

	while(true) {


		drfb.prevError = drfb.error; //Set the current error to the previous error
		drfb.error = drfb.target - nMotorEncoder[rightDRFB] / 627.2 * (1.0/7.0) * 360.0 + 40;
		//degrees - ticks / (ticks/rotation) * (gr constant) * (degrees/rotation)
		//degrees - degrees

		drfb.proportion = drfb.error * drfb.KP; //Calculate the proportion
		drfb.integral += drfb.prevError * drfb.KI;
		drfb.derivative = (drfb.error - drfb.prevError) * drfb.KD; //Calculate the derivative

		drfb.output = drfb.proportion + drfb.integral + drfb.derivative; //Calculate the output
		drfb.output = drfb.output > 127 ? 127 : (drfb.output < -127 ? -127 : drfb.output);

		setSpeed(rightDRFB, drfb.output, true);


		cb.prevError = cb.error; //Set the current error to the previous error
		cb.error = cb.target - abs(nMotorEncoder[chainBar]) / 627.2 * (1.0/5.0) * 360.0;

		cb.proportion = cb.error * cb.KP; //Calculate the proportion
		cb.integral += cb.prevError * cb.KI;
		cb.derivative = (cb.error - cb.prevError) * cb.KD; //Calculate the derivative

		cb.output = cb.proportion + cb.integral + cb.derivative; //Calculate the output
		cb.output = cb.output > 127 ? 127 : (cb.output < -127 ? -127 : cb.output);

		//setSpeed(chainBar, cb.output, true);


		delay(20); //Wait for 20 ms


	}

}
