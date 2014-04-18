#ifndef _TIMERANIM_H
#define _TIMERANIM_H

#include "cD3DManager.h"
#include "cD3DXTexture.h"
#include "cD3DXSpriteMgr.h"
#include "Timer.h"
#include "GameInformation.h"

/*
	CLASS DEFINITION: Handles updating, drawing and animating a timer gauge on the screen
*/

class TimerAnim{

private:

	cD3DManager* d3dMgr;
	cD3DXSpriteMgr* d3dSRMgr;

	cD3DXTexture* sprayTextures[16]; //This will store all of the textures
	char path[50]; //The path for the textures (used to initialise all of the textures)

	int currFrame; //The current frame of animation

	Timer* gameTimer; //The game timer

	
public:


	TimerAnim(); //Default constructor
	~TimerAnim(); //Default destructor

	void Initialise(); //Initialises the timer
	void UpdateTimer(); //Updates the timer
	void ChangeFrame(); //Changes the frame
	void Draw(); //Draws the timer gauge
	bool GameOver(); //Returns true if final timer frame has been hit

};
#endif