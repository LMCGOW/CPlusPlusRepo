#ifndef _TIMER_H
#define _TIMER_H

#include "GameConstants.h"

/*
	CLASS DEFINITION: Handles updating the timer stuff
*/

class Timer{

private:

	__int64 frequency;
	float seconds;

	__int64 currentTime;
	__int64 previousTime;


public:

	Timer(); //Default constructor
	~Timer(); //Default destructor

	bool TimePassed(float time); //Returns true if the time passed is more than the "time" variable passed in

};

#endif