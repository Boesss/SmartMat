#include "TemperatureSensor.h"

TemperatureSensor::TemperatureSensor(uint8_t id, uint8_t pin, float changerate) :
	_id(id), _pin(pin), _changerate(changerate) {
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

float TemperatureSensor::readChangeTemp(const unsigned milliseconds) {
	int count = 0;
	float temperature = 0;
	Timer timer;

	// Set _oldTemperature to temperature for first run
	if (_oldTemperature == 0) {
		_oldTemperature = readTemperature();
	}

	float oldTemperature = _oldTemperature;

	while (1) {
		count++;
		temperature += readTemperature();
		if (timer.getDurationNow() > milliseconds) {
			break;
		}
	}

	temperature /= count;

	_oldTemperature = temperature;

	return temperature - oldTemperature;
}

bool TemperatureSensor::checkRiseTemp(const unsigned milliseconds) {

	if (readChangeTemp(milliseconds) > _changerate) {
		return true;
	}
	return false;
}