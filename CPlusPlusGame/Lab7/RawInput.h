#ifndef _RAWINPUT_H
#define _RAWINPUT_H

#include "GameConstants.h"

class RawInput{

public:
	void Initialise(HWND hwnd);

	static RawInput* GetInst();

private:
	static RawInput* rawInp;


};

#endif