#include "PressureSensor.h"

PressureSensor::PressureSensor(uint8_t id, uint8_t pin, float treshhold) : 
	_id(id), _pin(pin), treshhold_resistance(treshhold) {
	pinMode(_pin, INPUT);
	analogReference(DEFAULT);
}

float PressureSensor::readResistance() {
	return float(_resistance * analogRead(_pin)) /
		float(1023 - analogRead(_pin));
}

bool PressureSensor::read() {
	if (readResistance() < treshhold_resistance) {
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

//bool PressureSensor::read(const unsigned milliseconds) {
//	timer.start();
//	while (timer.getDurationNow() < milliseconds) {
//		if (read() == false) {
//			return false;
//		}
//	}
//	return true;
//}