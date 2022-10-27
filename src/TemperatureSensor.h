// TemperatureSensor.h

#ifndef _TEMPERATURESENSOR_h
#define _TEMPERATURESENSOR_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "Timer.h"
#include "Power.h"

class TemperatureSensor {

private:
	uint8_t _id;
	uint8_t _pin;
	float _oldTemperature;
	bool _change;
	float _changerate = 0;

	static const unsigned _resistance = 100; // In kOhm

	// Read the resistance of the NTC-resistor using the voltage
	float readResistance();

	// The transfer function for calculating the temperature from the resistance
	float transferFunction(const float& resistance);

public:
	// Constructor for a TemperatureSensor
	TemperatureSensor(uint8_t id, uint8_t pin, float changerate);

	// Read the temperature in celcius
	float readTemperature();

	// Reads the rate of change over milliseconds
	float readChangeTemp(const unsigned milliseconds);

	// Checks if there is change in temperature for a specfic rate of change in celcius over milliseconds
	// True if outside of rate of change
	bool checkRiseTemp(const unsigned milliseconds);

};


#endif
