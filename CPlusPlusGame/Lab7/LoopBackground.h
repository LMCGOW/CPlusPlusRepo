#ifndef _LOOPBACKGROUND_H
#define _LOOPBACKGROUND_H

#include "GameConstants.h"
#include "cD3DManager.h"
#include "cD3DXSpriteMgr.h"
#include "cD3DXTexture.h"

/*
	CLASS DEFINITION: Creates a scrolling background
*/


class LoopBackground{


private:

	//The necessary device interfaces
	cD3DManager* d3dMgr;
	cD3DXSpriteMgr* d3dSRMgr;
	
	//The background textures
	cD3DXTexture* bg1;
	cD3DXTexture* bg2;

	D3DXVECTOR3 bg1pos; //Background one position
	D3DXVECTOR3 bg2pos; //Background two position

public:

	LoopBackground(); //Default constructor
	~LoopBackground(); //Default destructor

	void Loop(); //Loops backgrounds
	void DrawBackgrounds(); //Draws the backgrounds
	void Initialise(); //Initialises the class


};

#endif