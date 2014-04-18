/*
=================
main.cpp
Main entry point for the Card application
=================
*/

#include "GameConstants.h"
#include "GameResources.h"
#include "cD3DManager.h"
#include "cD3DXSpriteMgr.h"
#include "cD3DXTexture.h"
#include "cBalloon.h"
#include "cSprite.h"
#include "cExplosion.h"
#include "cXAudio.h"
#include "cD3DXFont.h"
#include "ScreenManager.h"
#include "RawInput.h"

using namespace std;

HINSTANCE hInst; // global handle to hold the application instance
HWND wndHandle; // global variable to hold the window handle

// Get a reference to the DirectX Manager
static cD3DManager* d3dMgr = cD3DManager::getInstance();

// Get a reference to the DirectX Sprite renderer Manager 
static cD3DXSpriteMgr* d3dxSRMgr = cD3DXSpriteMgr::getInstance();

RECT clientBounds; //The dimensions of the window

TCHAR szTempOutput[30];

ScreenManager* screenMgr; //A pointer to the screen manager

//Forward declarations for the methods used to instantiate the game objects and subsequently update them
#pragma region
void InstantiateGameObjects();
void UpdateGameObjects();
#pragma endregion Forward Declarations


/*
==================================================================
* LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam,
* LPARAM lParam)
* The window procedure
==================================================================
*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// Check any available messages from the queue
	switch (message)
	{

		case WM_LBUTTONDOWN:
		{
			//Get the mouse information
			POINT mouse;
			mouse.x = LOWORD(lParam);
			mouse.y = HIWORD(lParam);

			//Pass the mouse information into the screen manager
			screenMgr->LeftButtonClicked(mouse);

		}
		case WM_KEYDOWN:
			{
				//Passes the key pressed information to the screen manager
				screenMgr->HandleInput(wParam, "pressed");

				return 0;
			}

		case WM_KEYUP:
			{
				//Passes the key pressed information to the screen manager
				screenMgr->HandleInput(wParam, "released");

				return 0;

			}
		case WM_CLOSE:
			{
			// Exit the Game
				PostQuitMessage(0);
				 return 0;
			}

		case WM_DESTROY:
			{
				PostQuitMessage(0);
				return 0;
			}

	}

	// Always return the message to the default window
	// procedure for further processing
	return DefWindowProc(hWnd, message, wParam, lParam);
}

#pragma region
/*
==================================================================
* bool initWindow( HINSTANCE hInstance )
* initWindow registers the window class for the application, creates the window
==================================================================
*/
bool initWindow( HINSTANCE hInstance )
{
	WNDCLASSEX wcex;
	// Fill in the WNDCLASSEX structure. This describes how the window
	// will look to the system
	wcex.cbSize = sizeof(WNDCLASSEX); // the size of the structure
	wcex.style = CS_HREDRAW | CS_VREDRAW; // the class style
	wcex.lpfnWndProc = (WNDPROC)WndProc; // the window procedure callback
	wcex.cbClsExtra = 0; // extra bytes to allocate for this class
	wcex.cbWndExtra = 0; // extra bytes to allocate for this instance
	wcex.hInstance = hInstance; // handle to the application instance
	wcex.hIcon = LoadIcon(hInstance,IDI_APPLICATION); // icon to associate with the application
	wcex.hCursor = LoadCursor(hInstance, IDC_ARROW);// the default cursor
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW+1); // the background color
	wcex.lpszMenuName = NULL; // the resource name for the menu
	wcex.lpszClassName = "SpaceBattle"; // the class name being created
	wcex.hIconSm = LoadIcon(hInstance,IDI_APPLICATION); // the handle to the small icon

	RegisterClassEx(&wcex);
	// Create the window
	wndHandle = CreateWindow("SpaceBattle",			// the window class to use
							 "Space Battle",			// the title bar text
							WS_OVERLAPPEDWINDOW,	// the window style
							CW_USEDEFAULT, // the starting x coordinate
							CW_USEDEFAULT, // the starting y coordinate
							800, // the pixel width of the window
							600, // the pixel height of the window
							NULL, // the parent window; NULL for desktop
							NULL, // the menu for the application; NULL for none
							hInstance, // the handle to the application instance
							NULL); // no values passed to the window
	// Make sure that the window handle that is created is valid
	if (!wndHandle)
		return false;

	// Display the window on the screen
	ShowWindow(wndHandle, SW_SHOW);
	UpdateWindow(wndHandle);
	return true;
}
#pragma endregion windowInitialisation


/*
==================================================================
// This is winmain, the main entry point for Windows applications
==================================================================
*/
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow )
{

#pragma region
	// Initialize the window
	if ( !initWindow( hInstance ) )
		return false;
	// called after creating the window
	if ( !d3dMgr->initD3DManager(wndHandle) )
		return false;
	if ( !d3dxSRMgr->initD3DXSpriteMgr(d3dMgr->getTheD3DDevice()))
		return false;
#pragma endregion initialisationStuff
	


#pragma region 

	// Grab the frequency of the high def timer
	__int64 freq = 0;				// measured in counts per second;
	QueryPerformanceFrequency((LARGE_INTEGER*)&freq);
	float sPC = 1.0f / (float)freq;			// number of seconds per count

	__int64 currentTime = 0;				// current time measured in counts per second;
	__int64 previousTime = 0;				// previous time measured in counts per second;

	float numFrames   = 0.0f;				// Used to hold the number of frames
	float timeElapsed = 0.0f;				// cumulative elapsed time

	GetClientRect(wndHandle,&clientBounds);

	float fpsRate = 1.0f/25.0f;

#pragma endregion FPSstuff

	
#pragma region
	LPDIRECT3DSURFACE9 theBackbuffer = NULL;  // This will hold the back buffer
	
	MSG msg;
	ZeroMemory( &msg, sizeof( msg ) );
	
	QueryPerformanceCounter((LARGE_INTEGER*)&previousTime);
#pragma endregion Setup background

	//Instantiates a new player object
	InstantiateGameObjects();

	while( msg.message!=WM_QUIT )
	{
		// Check the message queue
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
		else
		{

#pragma region
			// Game code goes here
			QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);
			float dt = (currentTime - previousTime)*sPC;

			// Accumulate how much time has passed.
			timeElapsed += dt;
#pragma endregion fpsStuff

			/*
			==============================================================
			| Update the postion of the balloons and check for collisions
			==============================================================
			*/
			if(timeElapsed > fpsRate)
			{

				//Update the game objects
				UpdateGameObjects();

				//render starts here
				d3dMgr->beginRender();

				theBackbuffer = d3dMgr->getTheBackBuffer();
			
				//Draw the surfaces via the screen manager
				screenMgr->DrawSurface(theBackbuffer);

				d3dxSRMgr->beginDraw();

				//Draw the sprites via the screen manager
				screenMgr->Draw();

				d3dxSRMgr->endDraw();

				//Draw the text via the screen manager
				screenMgr->DrawTextScreen();

				d3dMgr->endRender();

				timeElapsed = 0.0f;
			}

			previousTime = currentTime;
		}
	}
	d3dxSRMgr->cleanUp();
	d3dMgr->clean();
	return (int) msg.wParam;
}

/*
	instantiates the game objects
*/
void InstantiateGameObjects(){

	screenMgr = new ScreenManager();

}

/*
	updates game objects
*/
void UpdateGameObjects()
{
	screenMgr->Update();

}
