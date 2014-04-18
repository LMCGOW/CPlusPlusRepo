#ifndef _MENUSCREEN_H
#define _MENUSCREEN_H

class ScreenManager;

#include "cD3DManager.h"
#include "GameInformation.h"
#include "cD3DXTexture.h"
#include "cD3DXSpriteMgr.h"

/*
	CLASS DEFINITION: Updates and draws menu screen
*/

class MenuScreen{

private:

	LPDIRECT3DSURFACE9 screen;
	cD3DManager* d3dMgr;
	cD3DXSpriteMgr* d3dSRMgr;

public:

	MenuScreen(); //Default constructor

	void Update(); //Updates the menu screen
	void DrawSurface(LPDIRECT3DSURFACE9 theBackBuffer); //Draws menu screen surfae
	void Draw(); //Draws menu screen objects
	void Initialise(); //Initialises menu screen
	void HandleInput(WPARAM wParam, string keyState); //Handles menu screen input
	
	bool PlayButtonClicked(POINT mouse); //Checks if play button has been clicked

	cD3DXTexture* playButtonTex;
	D3DXVECTOR3 playButtonPos;
	RECT playButton;
	
};

#endif