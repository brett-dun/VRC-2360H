
task autonomous() {

	clearLCD(); //Clear the LCD

	enable(); //Enable the smart motors

	if(skillsEnabled) //If true
		skills(); //Run robot skills code
	else { //Otherwise
		displayLCDCenteredString(0, "Running:"); //Display "Running" on top
		displayLCDCenteredString(1, autonOptions[autoChoice]);
		playSoundFile("CantinaBandClip.wav"); //Begin playing music
		switch(autoChoice) { //Select a normal autonomous program
			case 1: auto1(); break;
			case 2: auto2(); break;
			case 3: auto3(); break;
			case 4: auto4(); break;
			default: break; //Don't run anything
		}
	}

	clearLCD(true); //Clear the LCD
	displayLCDCenteredString(0, "Done");

}
