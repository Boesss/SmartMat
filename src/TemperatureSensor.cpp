#include "TemperatureSensor.h"

TemperatureSensor::TemperatureSensor(uint8_t id, uint8_t pin): _id(id), _pin(pin) {
	pinMode(_pin, INPUT);
	analogReference(DEFAULT);
}

float TemperatureSensor::readResistance() {
	return float(_resistance * analogRead(_pin)) /
	float(1023 - analogRead(_pin));
}

float TemperatureSensor::transferFunction(const float& resistance) {
	return 159.7 - 0.0790 * resistance + 4.563 * sqrt(resistance) - 37.47 * log(resistance);
}

float TemperatureSensor::readTemperature() {
	return transferFunction(readResistance());
}

bool TemperatureSensor::checkChange(const unsigned milliseconds, const float changerate) {
	if (timer.getDurationNow() > milliseconds) {

		// Reset timer;
		timer.start();

		if (abs(readTemperature() - _oldTemperature) < changerate) {
			_change = false;
		}
		else {
			_change = true;
		}

		// Save old temperature
		_oldTemperature = readTemperature();
	}
	return _change;
}
