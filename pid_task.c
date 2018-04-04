#pragma systemFile //This prevents "Unreference variable" and "Unreferenced function" warnings

typedef struct {

	bool enabled;

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
PIDController mgl;

void setDRFBAngle(const float angle) {
	drfb.enabled = true;
	drfb.target = angle;
}

void setCBAngle(const float angle) {
	cb.enabled = true;
	cb.target = angle;
}

void setMGLAngle(const float angle) {
	mgl.enabled = true;
	mgl.target = angle;
}

void disableDRFBPID() {
	drfb.enabled = false;
}

void disableCBPID() {
	cb.enabled = false;
}

void disableMGLPID() {
	mgl.enabled = false;
}

task pidTask() {

	//double reverse four bar
	drfb.KP = 10.;
	drfb.KI = 0;
	drfb.KD = 1.;

	//chain bar
	cb.KP = 5.;
	cb.KI = 0.;
	cb.KD = 1.;

	mgl.KP = 30.;
	mgl.KI = 0.;
	mgl.KD = 20.;

	while(true) {

		drfb.prevError = drfb.error; //Set the current error to the previous error
		drfb.error = drfb.target - (nMotorEncoder[leftDRFB] / 392. * (1.0/7.0) * 360.0) + 50;
		//degrees - ticks / (ticks/rotation) * (gr constant) * (degrees/rotation)
		//degrees - degrees

		drfb.proportion = drfb.error * drfb.KP; //Calculate the proportion
		drfb.integral += drfb.prevError * drfb.KI;
		drfb.derivative = (drfb.error - drfb.prevError) * drfb.KD; //Calculate the derivative

		drfb.output = drfb.proportion + drfb.integral + drfb.derivative; //Calculate the output
		drfb.output = drfb.output > 127 ? 127 : (drfb.output < -127 ? -127 : drfb.output);

		if(drfb.enabled)
			setSpeedImmediate(leftDRFB, drfb.output);


		cb.prevError = cb.error; //Set the current error to the previous error
		cb.error = cb.target - ((SensorValue[potentiometer]-2310)/(4070.-2310.)*90);

		cb.proportion = cb.error * cb.KP; //Calculate the proportion
		cb.integral += cb.prevError * cb.KI;
		cb.derivative = (cb.error - cb.prevError) * cb.KD; //Calculate the derivative

		cb.output = cb.proportion + cb.integral + cb.derivative; //Calculate the output
		cb.output = cb.output > 127 ? 127 : (cb.output < -127 ? -127 : cb.output);

		if(cb.enabled)
			setSpeedImmediate(chainBar, cb.output);

		mgl.prevError = mgl.error; //Set the current error to the previous error
		mgl.error = mgl.target + (nMotorEncoder[leftMobileGoal] / 392. * (1.0/5.0) * 360.0); //change this angle
		//degrees - ticks / (ticks/rotation) * (gr constant) * (degrees/rotation)
		//degrees - degrees

		mgl.proportion = mgl.error * mgl.KP; //Calculate the proportion
		mgl.integral += mgl.prevError * mgl.KI;
		mgl.derivative = (mgl.error - mgl.prevError) * mgl.KD; //Calculate the derivative

		//add some bounds to the integral
		mgl.integral = mgl.integral > 127 ? 127 : (mgl.integral < -127 ? -127 : mgl.integral);
		mgl.integral = (mgl.prevError <= 0. && mgl.error >= 0.) || (mgl.prevError >= 0. && mgl.error <= 0.) ? 0 : mgl.integral;

		mgl.output = mgl.proportion + mgl.integral + mgl.derivative; //Calculate the output
		mgl.output = mgl.output > 127 ? 127 : (mgl.output < -127 ? -127 : mgl.output);

		if(mgl.enabled)
			setSpeedImmediate(leftMobileGoal, mgl.output);


		delay(20); //Wait for 20 ms


	}

}
