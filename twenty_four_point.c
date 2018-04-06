
void auto5() { //drop cone on mobile goal, move mobile goal to five point zone

	auto1(true);
	driveInches(-45, true); //drive backward //check this

	if(leftStart)
		turnDegrees(155);
	else
		turnDegrees(-155);

	driveInches(4, true); //drive forward

	if(leftStart)
		turnDegrees(90);
	else
		turnDegrees(-90);

	driveInches(21.5, true); //drive forward
	//Place mobile goal into 20 point zone
	setMGLAngle(105);
	delay(750);
	setDRFBAngle(-40);
	driveInches( -20 ); //drive backward

}
