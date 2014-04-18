#include "RandomNumber.h"

RandomNumber* RandomNumber::instance = NULL;

/*
	Random number constructor
*/
RandomNumber::RandomNumber(){

	seedUnique =1;
	seedUnique2 = 20;
	seedUnique3 = 400;

	seedUniqueMultiplier = 3;
	seedUniqueDivisor = 1;
	seedUniqueModulus = 5;

}

/*
	Returns the random number instance
*/
RandomNumber* RandomNumber::GetInstance(){
	
	if(instance == NULL)
		instance = new RandomNumber();

	return instance;

}

/*
	Carries out a formula that is designed to produce a very random number
*/
int RandomNumber::GenerateRandomNumber(int dampener){

	int seed;

	seedUnique+=2;
	seedUnique2 += 6;
	seedUnique3 += 10;

	seedUniqueMultiplier += (time(NULL) * (seedUnique*time(NULL)));
	seedUniqueDivisor += seedUnique2 + (time(NULL) % seedUnique2);
	seedUniqueModulus += seedUnique3 * (time(NULL) * (seedUnique-seedUnique2 * (time(NULL))));

	seed = (seedUnique * seedUniqueMultiplier) + (seedUnique2 / seedUniqueDivisor) + (seedUnique3 % seedUniqueModulus);

	srand((unsigned int)(time(NULL) * (int)seed));

	int random;

	random = (1 + (rand() % dampener));

	return random;

}