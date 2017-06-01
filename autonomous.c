#define SKILLS 0

//Clear the LCD
clearLCDLine(0);
clearLCDLine(1);
bLCDBacklight = true; //Turn the LCD's backlight on
displayLCDCenteredString(0, "Running:"); //Display "Running" on top

if(SKILLS)
	skills();
else {
	switch(autoChoice) {
		case 4: displayLCDCenteredString(1, "Nothing"); break;
	}
}

//Clear the LCD
clearLCDLine(0);
clearLCDLine(1);
bLCDBacklight = true; //Turn the LCD's backlight on
displayLCDCenteredString(0, "Done");
