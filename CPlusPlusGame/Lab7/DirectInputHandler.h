#ifndef _DIRECTINPUTHANDLER_H
#define _DIRECTINPUTHANDLER_H

#include "GameConstants.h"

class DirectInputHandler{

private:
	LPDIRECTINPUT8  diObj; //Direct input object
	LPDIRECTINPUTDEVICE8 keyboardInp; //Keyboard device

	static DirectInputHandler* instance;

	BYTE keys[256];

public:
	DirectInputHandler();
	~DirectInputHandler();

	static DirectInputHandler* GetInstance();

	void Initialise(HINSTANCE hInst, HWND hwnd);
	void AcquireKeyboard();
	void Update();

	void CheckIfFailed();

	static bool GetKeyPressed(int input);
};
#endif