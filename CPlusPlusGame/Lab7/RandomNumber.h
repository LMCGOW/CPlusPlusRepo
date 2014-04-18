#ifndef _RANDOMNUMBER_H
#define _RANDOMNUMBER_H

#include "GameConstants.h"

/*
	CLASS DEFINITION: Custom random number class
*/

class RandomNumber{

private:
	static RandomNumber* instance;

	int seedUnique;
	int seedUnique2;
	int seedUnique3;

	int seedUniqueMultiplier;
	int seedUniqueDivisor;
	int seedUniqueModulus;

public:

	RandomNumber(); //Default constructor
	static RandomNumber* GetInstance(); //Returns the random number instance

	int GenerateRandomNumber(int dampener); //Generates a random number using a formula

};

#endif