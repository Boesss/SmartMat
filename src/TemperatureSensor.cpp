#include "TemperatureSensor.h"

TemperatureSensor::TemperatureSensor(uint8_t id, uint8_t pin): _id(id), _pin(pin) {
	pinMode(_pin, INPUT);
	analogReference(DEFAULT);
}

float TemperatureSensor::readResistance() {
	Power power(0, 7);
	return float(_resistance * analogRead(_pin)) /
	float(1023 - analogRead(_pin));
}

float TemperatureSensor::transferFunction(const float& resistance) {
	return 159.7 - 0.0790 * resistance + 4.563 * sqrt(resistance) - 37.47 * log(resistance);
}

float TemperatureSensor::readTemperature() {
	return transferFunction(readResistance());
}

bool TemperatureSensor::checkRiseTemp(const unsigned milliseconds, const float changerate) {
	int count = 0;
	float temperature = 0;
	timer.start();

	while(1){
		count++;
		temperature += readTemperature();
		if (timer.getDurationNow() > milliseconds) {
			break;
		}
	}

	temperature /= count;

	if ((temperature - _oldTemperature) > changerate) {
		_oldTemperature = temperature;
		return true;
	}
	_oldTemperature = temperature;
	return false;
}