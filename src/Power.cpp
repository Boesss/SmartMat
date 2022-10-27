#include "Power.h"

Power::Power(uint8_t id, uint8_t pin) : _id(id), _pin(pin) {
	pinMode(_pin, OUTPUT);
	digitalWrite(_pin, HIGH);
}

Power::~Power() {
	digitalWrite(_pin, LOW);
}