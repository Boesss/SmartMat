// Timer.h

#ifndef _TIMER_h
#define _TIMER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class Timer {
private:
	unsigned long _start, _end;

public:

	// Timer constructer, start the timer
	Timer();

	// Start the timer / resets the timer when started
	void start();
	
	// Stops the timer
	void stop();

	// Get the duration from start until stop
	int getDuration() const;

	// Get the duration from start unil now
	int getDurationNow() const;
};


#endif

