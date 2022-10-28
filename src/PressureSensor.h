// PressureSensor.h

#ifndef _PRESSURESENSOR_h
#define _PRESSURESENSOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Timer.h" 
#include "Power.h"

class PressureSensor {

private:
	uint8_t _id;
	uint8_t _pin;

	float treshhold_resistance = 0;

	static const unsigned _resistance = 10000; // In Ohm

	float readResistance();

public:
	// Constructor for a Pressure sensor
	PressureSensor(uint8_t id, uint8_t pin, float treshhold);

	// Returns a boolean value depending on the resistance of the sensor
	// Returns true for activation
	bool read();

	bool read(const unsigned milliseconds);

};


#endif

