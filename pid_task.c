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

PIDController mgl;

//0 = start, 35 = mobile goal cone drop position, 45 = highest point, 120 = extended
void setMGLAngle(float angle) {
	mgl.enabled = true;
	mgl.target = angle;
}

void disableMGLPID() {
	mgl.enabled = false;
}

task pidTask() {

	//mobile goal lift
	mgl.KP = 30.;
	mgl.KI = 0.;
	mgl.KD = 20.;

	while(true) {

		mgl.prevError = mgl.error; //Set the current error to the previous error
		mgl.error = mgl.target + (nMotorEncoder[leftMobileGoal] / 627.2 * (1.0/5.0) * 360.0); //change this angle
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
