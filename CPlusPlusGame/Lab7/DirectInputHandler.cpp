#include "DirectInputHandler.h"

DirectInputHandler* DirectInputHandler::instance = NULL;

DirectInputHandler::DirectInputHandler(){


}

DirectInputHandler::~DirectInputHandler(){
	
	if (keyboardInp)
	{
		keyboardInp->Unacquire();
		keyboardInp->Release();
	}

	if (diObj)
		diObj->Release();

}

DirectInputHandler* DirectInputHandler::GetInstance(){

	if(instance == NULL)
		instance = new DirectInputHandler();

	return instance;

}

void DirectInputHandler::Initialise(HINSTANCE hInst, HWND hwnd){

	HRESULT hr = DirectInput8Create(hInst, DIRECTINPUT_VERSION, 
        IID_IDirectInput8, (void**)&diObj, NULL);

	hr = diObj->CreateDevice(GUID_SysKeyboard, &keyboardInp, NULL);
	hr = keyboardInp->SetDataFormat(&c_dfDIKeyboard);
	hr = keyboardInp->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

}

void DirectInputHandler::AcquireKeyboard(){

	keyboardInp->Acquire();

	ZeroMemory(keys, sizeof(keys));
	keyboardInp->GetDeviceState(sizeof(keys), keys);

}

void DirectInputHandler::CheckIfFailed(){

	HRESULT hr=keyboardInp->GetDeviceState( sizeof(keys), keys );

if (FAILED(hr))
{
       hr=keyboardInp->Acquire();

       while( hr == DIERR_INPUTLOST ) 
       {          
             hr = keyboardInp->Acquire();
       }

       if (FAILED(hr))
         return;

       keyboardInp->GetDeviceState(sizeof(keys), keys);
}

}

void DirectInputHandler::Update(){


}

bool DirectInputHandler::GetKeyPressed(int input){

	if(input & 0x80)
		return true;

	else
		return false;

}
