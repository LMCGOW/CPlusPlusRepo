#include "Timer.h"

/*
	Timer class constructor
*/
Timer::Timer(){

	frequency =0;
	currentTime =0;
	previousTime =0;
	seconds = 0;

	QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
	seconds = 1.0f/(float)frequency;

}

Timer::~Timer(){

	

}

/*
	functions as a timer that is usable in all classes
*/
bool Timer::TimePassed(float time){

	if(previousTime == 0)
		QueryPerformanceCounter((LARGE_INTEGER*)&previousTime);

	QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);

	if(((currentTime - previousTime)*seconds) > time)	{
	
		previousTime=currentTime;
		return true;

	}
	else
		return false;

}