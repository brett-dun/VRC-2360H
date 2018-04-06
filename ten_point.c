
void auto4() { //drop cone on mobile goal, move mobile goal to five point zone

	auto1();

	driveInches(-45);

	if(leftStart)
		turnDegrees(210);
	else
		turnDegrees(-210);

	driveInches(8, true);

	setMGLAngle(120);
	delay(750);

	driveInches(-10);
	//setDRFBAngle(-40);

}
