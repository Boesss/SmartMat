#include <Servo.h>

#include "Logic.h"
#include "TemperatureSensor.h"
#include "PressureSensor.h"
#include "Timer.h"

// IO Pins for the different classes
constexpr uint8_t PRESPIN = A2;
constexpr uint8_t TEMPPIN = A1;
constexpr uint8_t MOTORPIN = 3;

// Constants
constexpr int SHUTOFFDURATION = 15000; // In milliseconds

// Constructors for all the classes
PressureSensor sensor_p(1, PRESPIN, 0.1); // Treshhold 0.1 kOhm, around 5 kg.
TemperatureSensor sensor_t(1, TEMPPIN, 0.2); // Rate of change 0.2 celcius
Servo servo;
Timer timout;

// Shower States
enum class Shower {
	On,
	Off,
	Warming
};

//Global variables
Shower showerstate = Shower::Off;
bool timerstate = false;
float surroundtemp = 21; // Standard set to 21 degrees celcius

// ARDUINO SETUP
void setup() {
	Serial.begin(9600);
	servo.attach(MOTORPIN);
	Serial.println("SmartMat initialised");
}

// ARDUINO LOOP
void loop() {

	//printTempDebug();

	//printDebug();

	showerLoop();

}

// Main function
int showerLoop() {

	// Shower off state
	if (showerstate == Shower::Off) {
		// Reads temperature to set the surrounding temperature
		surroundtemp = sensor_t.readTemperature();

		// Checks if pressure is applied to the mat
		if (sensor_p.read(500)) {
			showerstate = Shower::Warming;
			timout.start();
			Serial.println("State: Warming");
			openShowerHead();
		}
	}

	// Shower warming state
	else if (showerstate == Shower::Warming) {

		//Checks the change in temperature
		if (!sensor_t.checkRiseTemp(500) && (sensor_t.readTemperature() > (surroundtemp + 1))) {
			showerstate = Shower::On;
			Serial.println("State: On");
			closeShowerHead();
		}

		// Timout
		if (timout.getDurationNow() > SHUTOFFDURATION) {
			showerstate = Shower::Off;
			Serial.println("State: Off");
		}
	}

	// Shower on state
	else if (showerstate == Shower::On) {

		// Checks if pressure is applied to the mat
		if (sensor_p.read(100)) {
			openShowerHead();
			timerstate = false;
		}
		else {
			closeShowerHead();
			if (!timerstate) {
				timerstate = true;
				timout.start();
			}
		}

		// Set showerstate to off
		if ((timout.getDurationNow() > SHUTOFFDURATION) && !sensor_p.read()) {
			showerstate = Shower::Off;
			Serial.println("State: Off");
		}
	}
}

// Motor functions
void openShowerHead() {
	servo.write(100);
}

void closeShowerHead() {
	servo.write(90);
}

//Debug functions
void printTempDebug() {
	Serial.print("Temperature: ");
	Serial.print(sensor_t.readTemperature()); // Temperature in celcius
	Serial.print(", Rate of change: ");
	Serial.println(sensor_t.readChangeTemp(500));
}

void printDebug() {
	Serial.print("Temperature: ");
	Serial.print(sensor_t.readTemperature()); // Temperature in celcius
	Serial.print(", Pressure mat: ");
	Serial.print(sensor_p.read()); // Pressure mat in bool
	Serial.print(", Rotation:  ");
	Serial.println(servo.read()); // Rotation in degrees
}

void writeMotorMonitor() {
	if (Serial.available()) {
		String cmd = Serial.readString();
		servo.write(cmd.toInt());
	}
}