#include "Vector.h"
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
constexpr int MINTEMPERATURE = 25;
constexpr int SHUTOFFDURATION = 15000; // In milliseconds

// Constructors for all the classes
PressureSensor sensor_p(1, PRESPIN);
TemperatureSensor sensor_t(1, TEMPPIN);
Servo servo;
Timer timer;

// Shower States
enum class Shower {
	On, 
	Off,
	Warming
};

//Global variables
Shower showerstate = Shower::Off;
bool timerstate = false;

// ARDUINO SETUP
void setup() {
	Serial.begin(9600);
	servo.attach(MOTORPIN);
}

// ARDUINO LOOP
void loop() {

	//printTempDebug();

	showerLoop();

}

// Main function
int showerLoop() {

	// Shower off state
	if (showerstate == Shower::Off) {
		// Checks if pressure is applied to the mat
		if (sensor_p.read(500)) {
			showerstate = Shower::Warming;
			Serial.println("State: Warming");
			openShowerHead();
		}
	}

	// Shower warming state
	else if (showerstate == Shower::Warming) {
		//Checks the change in temperature
		if (!sensor_t.checkRiseTemp(500, 0.2) && (sensor_t.readTemperature() > MINTEMPERATURE)) {
			showerstate = Shower::On;
			Serial.println("State: On");
			closeShowerHead();
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
				timer.start();
			}
		}

		// Set showerstate to off
		if ((timer.getDurationNow() > SHUTOFFDURATION) && !sensor_p.read()) {
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
	Serial.print(", Temp Change: ");
	Serial.println(sensor_t.checkRiseTemp(500, 0.2));
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
