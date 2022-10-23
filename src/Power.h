// Power.h

#ifndef _POWER_h
#define _POWER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class Power {
	
private:
	uint8_t _id;
	uint8_t _pin;

public:
	// Set a digital pin for providing the power, cannot exceed 40mA.
	// Turn the power to 5V for the length of the scope.
	Power(uint8_t id, uint8_t pin);
	~Power();

};


#endif

