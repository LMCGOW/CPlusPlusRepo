#ifndef _SCREENMANAGER_H
#define _SCREENMANAGER_H

#include "Screens.h"
#include "MenuScreen.h"
#include "GameScreen.h"
#include "GameOverScreen.h"
#include "InstructionsScreen.h"

/*
	CLASS DEFINITION: Updates screen manager class which handles managing all of the screens
*/

class ScreenManager{

private:
	
#pragma region
	
	MenuScreen menuScreen;
	GameScreen gameScreen;
	GameOverScreen gameOver;
	InstructionsScreen instructions;

	//I'm the Batman
#pragma endregion Screens

	Screens activeScreen; //Stores the active screen
	cD3DManager* d3dMgr;

	static ScreenManager* instance;

public:

	ScreenManager(); //Default constructor

	void Update(); //Updates the screen manager
	void FixedUpdate();
	void DrawSurface(LPDIRECT3DSURFACE9 theBackbuffer); //Draws all the screens
	void Draw(); //Draws the other screen stuff
	void SetActiveScreen(Screens active); //Will set the active screen
	void HandleInput(WPARAM wParam, string keyState); //Handles input for screens
	void KeyboardPressed(); //Handles a particular key press for screens
	void RestartGame(); //Restarts game
	void DrawTextScreen(); //Draws text on screens
	void LeftButtonClicked(POINT mouse); //Checks if left button has been clicked

	Screens ReturnActiveScreen(); //Will return the active screen
	static ScreenManager* GetInstance(); //Returns screen manager instance

	

};
#endif