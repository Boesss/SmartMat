// PressureSensor.h

#ifndef _PRESSURESENSOR_h
#define _PRESSURESENSOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Timer.h"

class PressureSensor {

private:
	uint8_t _id;
	uint8_t _pin;
	Timer timer;

public:
	// Constructor for a Pressure sensor
	PressureSensor(uint8_t id, uint8_t pin);
	
	// Returns true if pressure is applied
	bool read();

	// Returns if pressure is measured over time in milliseconds
	bool read(const unsigned milliseconds);

};


#endif

