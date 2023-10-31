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

#include "B_Stepper.h"


B_Stepper::B_Stepper(uint8_t rpm=DEFAULT_RPM){
	this->_delay = calcDelay(rpm);
}


B_Stepper::B_Stepper(uint8_t in1, uint8_t in2, uint8_t in3, uint8_t in4)
{
	setPins(in1,in2,in3,in4);
	this->_delay = calcDelay(DEFAULT_RPM);
}

void B_Stepper::setSteps(int steps)
{
	if (steps==N_STEP_1 or steps==N_STEP)
		this->_totalSteps = steps;
	else
		this->_totalSteps = N_STEP;
}

void B_Stepper::setPins(uint8_t in1, uint8_t in2, uint8_t in3, uint8_t in4)
{
	this->_pins[0] = in1;
	this->_pins[1] = in2;
	this->_pins[2] = in3;
	this->_pins[3] = in4;

	PinsMode();
}

void B_Stepper::PinsMode(void){
	for (int i = 0; i < 4; ++i)
	{
		pinMode(this->_pins[i], OUTPUT);
		digitalWrite(this->_pins[i], LOW);
	}
}

void B_Stepper::move(bool sens=true)
{
	static unsigned long t = micros();
	this->_sens = sens;
	if(this->_sens==true){// Sens 1
		if(this->_stepsLeft > 0)
		{
			if((micros()-t) > this->_delay)
			{
				moveCW();
				--this->_stepsLeft;
				++this->_stepN;
				t=micros();
			}
		}
		else
			stop();
	}
	else // Sens 2
	{
		if(this->_stepsLeft > 0)
		{
			if((micros()-t) > this->_delay)
			{
				moveCCW();
				--this->_stepsLeft;
				++this->_stepN;
				t=micros();
			}
		}
		else
			stop();
	}
}

void B_Stepper::newMove (int numSteps=N_STEP)
{
	if(numSteps > 0 and numSteps <= this->_totalSteps)
		this->_stepsLeft = numSteps;
	else
		this->_stepsLeft = this->_totalSteps;
	
	this->_stepN = 0;
}

void B_Stepper::newMoveDeg(int Deg=360)
{
	int angle = Deg;

	if(angle > 0 and angle <= 360)
		angle = Deg;
	else
		angle = 360;

	this->_stepsLeft = map(angle,0, 360, 0, this->_totalSteps);
	this->_stepN = 0;
}

void B_Stepper::stop(void){
	for (int i = 0; i < 4; ++i)
		digitalWrite(this->_pins[i], LOW);
}

//----------------------PRIVATE----------------------

void B_Stepper::moveCCW(void)
{
	switch(this->_nSeq){
		case 0: 
			digitalWrite(this->_pins[0], 1);
			digitalWrite(this->_pins[1], 0);
			digitalWrite(this->_pins[2], 0);
			digitalWrite(this->_pins[3], 1);
			break;
		case 1: 
			digitalWrite(this->_pins[0], 0);
			digitalWrite(this->_pins[1], 1);
			digitalWrite(this->_pins[2], 0);
			digitalWrite(this->_pins[3], 1);
			break;
		case 2: 
			digitalWrite(this->_pins[0], 0);
			digitalWrite(this->_pins[1], 1);
			digitalWrite(this->_pins[2], 1);
			digitalWrite(this->_pins[3], 0);
			break;
		case 3: 
			digitalWrite(this->_pins[0], 1);
			digitalWrite(this->_pins[1], 0);
			digitalWrite(this->_pins[2], 1);
			digitalWrite(this->_pins[3], 0);
			break;
	}
	delayMicroseconds(this->_delay);
	this->_nSeq = ++this->_nSeq % N_SEQ;
}

void B_Stepper::moveCW(void)
{
	switch(this->_nSeq){
		case 0: 
			digitalWrite(this->_pins[0], 0);
			digitalWrite(this->_pins[1], 1);
			digitalWrite(this->_pins[2], 0);
			digitalWrite(this->_pins[3], 1);
			break;
		case 1: 
			digitalWrite(this->_pins[0], 1);
			digitalWrite(this->_pins[1], 0);
			digitalWrite(this->_pins[2], 0);
			digitalWrite(this->_pins[3], 1);
			break;
		case 2: 
			digitalWrite(this->_pins[0], 1);
			digitalWrite(this->_pins[1], 0);
			digitalWrite(this->_pins[2], 1);
			digitalWrite(this->_pins[3], 0);
			break;
		case 3: 
			digitalWrite(this->_pins[0], 0);
			digitalWrite(this->_pins[1], 1);
			digitalWrite(this->_pins[2], 1);
			digitalWrite(this->_pins[3], 0);
			break;
	}
	delayMicroseconds(this->_delay);
	this->_nSeq = ++this->_nSeq % N_SEQ;
}

int B_Stepper::calcDelay (int rpm){
	
	this->_rpm = rpm;

	if (this->_rpm < DEFAULT_RPM){this->_rpm=DEFAULT_RPM;}
	else if (this->_rpm > RPM_MAX){this->_rpm=RPM_MAX;} // highest speed

	unsigned long d = 60000000 / (this->_totalSteps* (unsigned long) this->_rpm);
	
	return (int) d;
}