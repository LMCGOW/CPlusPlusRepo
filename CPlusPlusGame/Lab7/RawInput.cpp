#include "RawInput.h"

RawInput* RawInput::rawInp = NULL;

void RawInput::Initialise(HWND hwnd){

	RAWINPUTDEVICE Rid[1];
	Rid[0].usUsagePage = 0x01;
	Rid[0].usUsage = 0x06;
	Rid[0].dwFlags = RIDEV_INPUTSINK;
	Rid[0].hwndTarget = hwnd;

	if (RegisterRawInputDevices(Rid,1,sizeof(Rid[0])) == false)
	{
		MessageBox(NULL, "Device Registration failed", "Error",MB_OK);
		return;
	}

}

RawInput* RawInput::GetInst(){

	if(rawInp == NULL)
		rawInp = new RawInput();

	return rawInp;
}