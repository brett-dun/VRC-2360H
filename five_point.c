
void auto3() {

	auto1();

	driveInches(-40);

	if(leftStart)
		turnDegrees(205);
	else
		turnDegrees(-205);

	setMGLAngle(120);
	delay(750);

	driveInches(-20);
	setMGLAngle(70);

}
