#define SKILLS 0

SensorValue[sixBar] = 0;

	//Clear the LCD
	clearLCDLine(0);
	clearLCDLine(1);
	bLCDBacklight = true; //Turn the LCD's backlight on

displayLCDCenteredString(0, "Running:"); //Display "Running" on top

if(SKILLS)
	skills();
else {
	switch(autoChoice) {
		case 1: displayLCDCenteredString(1, "Left - Cube"); cube(true); break;
		case 2: displayLCDCenteredString(1, "Left - Back"); backStars(true); break;
		case 3: displayLCDCenteredString(1, "Left - Front"); frontStars(true); break;
		case 4: displayLCDCenteredString(1, "Nothing"); break;
		case 5: displayLCDCenteredString(1, "Right - Cube"); cube(false); break;
		case 6: displayLCDCenteredString(1, "Right - Back"); backStars(false); break;
		case 7: displayLCDCenteredString(1, "Right - Front"); frontStars(false); break;
	}
}

	//Clear the LCD
	clearLCDLine(0);
	clearLCDLine(1);
	bLCDBacklight = true; //Turn the LCD's backlight on
	displayLCDCenteredString(0, "Done"); //*/
