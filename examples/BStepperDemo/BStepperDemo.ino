/**
 * https://www.youtube.com/@OpenProgramming
 * Email: openprogramming23@gmail.com
 * Date: 21/10/2023
 * 
 * Author: Exaucé KIMBEMBE
 * 
 * Tested Platforms:
 * This library has been tested on Arduino and ESP32 platforms.
 * 
 * Arduino code to control a stepper motor using the "B_Stepper" library.
 * It initializes the motor, sets parameters, and continuously rotates the motor
 * in both directions, displaying position information through serial communication.
 * 
 */

#include <B_Stepper.h>// Include the B_Stepper library

B_Stepper moteur;// Create an instance of the B_Stepper class named "moteur"

bool sens=true;// Declare a boolean variable "sens" and initialize it to true (for direction)

void setup() {
	Serial.begin(115200);// Initialize serial communication at 115200 baud
	
	moteur.setPins(9,10,11,12);// Configure the pins for the stepper motor
	moteur.newMoveDeg(360);// Initialize a new movement of 360 degrees

	// Display motor parameters
	Serial.print("rpm : "); Serial.print(moteur.getRpm()); Serial.println(" tr/min");
	Serial.print("delay : "); Serial.print(moteur.getDelay()); Serial.println(" us");
	Serial.print("T_steps : "); Serial.print(moteur.getTotalSteps()); Serial.println(" pas");

	moteur.setRpm(100);// Set the motor's RPM to 100

	// Display the updated motor parameters
	Serial.print("rpm : "); Serial.print(moteur.getRpm()); Serial.println(" tr/min");
	Serial.print("delay : "); Serial.print(moteur.getDelay()); Serial.println(" us");
	Serial.print("T_steps : "); Serial.print(moteur.getTotalSteps()); Serial.println(" pas");	
	Serial.print("stepsLeft : "); Serial.print(moteur.getStepsLeft()); Serial.println(" pas");	
	Serial.print("stepN : "); Serial.print(moteur.getStep()); Serial.println(" pas");	
}

void loop() {;	
	if(moteur.getStepsLeft()<=0){
		sens = not sens;// Reverse the direction of movement when the remaining steps are zero
		moteur.newMoveDeg(360);// Initialize a new movement of 360 degrees
	}
	moteur.move(sens);// Move the motor in the current direction (sens)
	// Display the current position (number of steps)
	Serial.print("stepN : "); Serial.print(moteur.getStep()); Serial.println(" pas");
}