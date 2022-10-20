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

	Timer();

	void start();
	void stop();
	int getDuration() const;
	int getDurationNow() const;
};


#endif

