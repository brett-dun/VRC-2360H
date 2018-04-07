#pragma systemFile //This prevents "Unreference variable" and "Unreferenced function" warnings

/*
	Status:
	- testing required

	Issues/Ideas:
	-
*/
void intakeCone(uint32 time, bool reversed = false) {
	uint32 endTime = nSysTime + time;
	while(nSysTime < endTime)
		setSpeed(intake, reversed ? -127 : 127, true);
	setSpeedImmediate(intake, 0);
}

void releaseCone(int32 time) {
	intakeCone(time, true);
}
