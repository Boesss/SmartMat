// TemperatureSensor.h

#ifndef _TEMPERATURESENSOR_h
#define _TEMPERATURESENSOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Timer.h"

class TemperatureSensor {

private:
	uint8_t _id;
	uint8_t _pin;
	float _oldTemperature;
	bool _change;
	Timer timer;

	static const unsigned _resistance = 100; // In kOhm

	// Read the resistance of the NTC-resistor using the voltage
	float readResistance();

	// The transfer function for calculating the temperature from the resistance
	float transferFunction(const float& resistance);
	
public:
	// Constructor for a TemperatureSensor
	TemperatureSensor(uint8_t id, uint8_t pin);

	// Read the temperature in celcius
	float readTemperature();

	// Checks if there is change in temperature for a specfic rate of change in celcius over milliseconds
	// True if outside of rate of change
	bool checkChange(const unsigned milliseconds, const float changerate);

};


#endif

