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
 * Description:
 * This C++ library allows you to control a stepper motor using an Arduino.
 * It provides a convenient interface for controlling the motor's movement and speed.
 * The library uses a 4-step sequence for two different senses (Sense 1 and Sense 2).
 * Each sense has a corresponding truth table.
 * 
 * Sense 1 uses a 4-step sequence: A  A' B  B'
 *							 	   1  0  0  1
 *							       0  1  0  1
 *							       0  1  1  0
 *							       1  0  1  0
 * 
 * Sense 2 uses a 4-step sequence: A  A' B  B'
 *								   0  1  0  1
 *								   1  0  0  1
 *								   1  0  1  0
 *								   0  1  1  0
 * Disclaimer:
 * This library is provided "as is," and the author is not responsible for any malfunction 
 * or damage to hardware resulting from its use. Use this library at your own risk, 
 * and ensure proper precautions when interfacing with hardware.
 * 
 */

#ifndef B_STEPPER
#define B_STEPPER

#ifndef __AVR__ || ESP32
	#error "This library has been tested on Arduino and ESP32 platforms."
#endif


#include "Arduino.h"

#define N_STEP 		400
#define N_STEP_1    200
#define N_SEQ       4
#define DEFAULT_RPM 22
#define RPM_MAX     130

class B_Stepper
{
	public:
		B_Stepper(uint8_t rpm=DEFAULT_RPM);// Initialize a stepper motor with a default or custom RPM setting
		B_Stepper(uint8_t in1, uint8_t in2, uint8_t in3, uint8_t in4);// Initialize a stepper motor with custom input pins

		void setSteps(int steps);// Set the number of steps in a movement
		void setPins(uint8_t in1, uint8_t in2, uint8_t in3, uint8_t in4);// Set the input pins for the motor
		void setRpm(uint8_t rpm){this->_delay = calcDelay(rpm);}// Set the RPM (rotations per minute) for the motor
		
		int getRpm(void){return this->_rpm;}// Get the current RPM setting
		int getDelay(void){ return this->_delay;}// Get the current delay in microseconds between steps
		int getTotalSteps(void){return this->_totalSteps;}// Get the total number of steps in a movement 
		int getStepsLeft() { return this->_stepsLeft;}// Get the number of steps left in the current movement
		int getStep() { return this->_stepN; }// Get the current miniStep position

		void move(bool sens=true);// Start moving the motor in a specified direction (default is clockwise)
		void newMove(int numSteps=N_STEP);// Initiate a new movement with a specified number of steps
		void newMoveDeg(int Deg=360);// Initiate a new movement with a specified number of degrees
		void stop(void);// Stop the motor's movement

	private:
		/*
        * @brief Set the mode of the input pins as OUTPUT.
        * This function is called to configure the input pins of the stepper motor driver as OUTPUT.
        */
		void PinsMode(void);
		/**
         * @brief Calculate the microsecond delay between steps for a given RPM.
         * @param rpm The desired RPM (rotations per minute).
         * @return The calculated delay in microseconds between steps.
         */
		int calcDelay(int rpm); 
		/**
         * @brief Move the motor in the clockwise direction (Sense 1).
         * This function is used to move the stepper motor in the clockwise direction using Sense 1 sequence.
         */
		void moveCW(void);
		/**
         * @brief Move the motor in the counterclockwise direction (Sense 2).
         * This function is used to move the stepper motor in the counterclockwise direction using Sense 2 sequence.
         */
		void moveCCW(void);

		bool _sens = true; // Flag to store the current movement direction (default is true for clockwise)
        int _pins[4];      // Array to store the input pins configuration
        int _nSeq = 0;     // Counter for the current step in the sequence
        int _delay;        // Current delay between steps in microseconds
        int _totalSteps = N_STEP; // Total number of steps in a movement
        int _stepsLeft = 0;       // Number of steps left in the current movement
        int _stepN = 0;           // Current miniStep position
        uint8_t _rpm = DEFAULT_RPM; // Current RPM setting
};
#endif