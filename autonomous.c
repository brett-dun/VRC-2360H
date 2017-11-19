

//Clear the LCD
clearLCDLine(0);
clearLCDLine(1);
bLCDBacklight = true; //Turn the LCD's backlight on
displayLCDCenteredString(0, "Running:"); //Display "Running" on top

enable(); //Enable the smart motors

if(skillsEnabled) //If true
	skills(); //Run robot skills code
else { //Otherwise
	switch(autoChoice) { //Select a normal autonomous program
		case 0: displayLCDCenteredString(1, "Nothing"); break; //Don't run anything
	}
}

//Clear the LCD
clearLCDLine(0);
clearLCDLine(1);
bLCDBacklight = true; //Turn the LCD's backlight on
displayLCDCenteredString(0, "Done");
