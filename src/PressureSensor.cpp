#include "PressureSensor.h"

PressureSensor::PressureSensor(uint8_t id, uint8_t pin) : _id(id), _pin(pin) {
	pinMode(_pin, INPUT);
	analogReference(DEFAULT);
}

bool PressureSensor::read() {
	if (analogRead(_pin) != 0) {
		return true;
	}
	return false;
}

bool PressureSensor::read(const unsigned milliseconds) {
	timer.start();
	while (timer.getDurationNow() < milliseconds) {
		if (read() == false) {
			return false;
		}
	}
	return true;
}