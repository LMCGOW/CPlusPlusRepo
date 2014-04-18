#ifndef _INSTRUCTIONSSCREEN_H
#define _INSTRUCTIONSSCREEN_H

#include <d3dx9.h>

#include "cD3DManager.h"
#include "cD3DXSpriteMgr.h"

class InstructionsScreen{

private:
	LPDIRECT3DSURFACE9 screen;
	
	cD3DManager* d3dMgr;
	cD3DXSpriteMgr* d3dSRMgr;

public:
	InstructionsScreen();
	~InstructionsScreen();

	void Initialise();
	void DrawSurface(LPDIRECT3DSURFACE9 theBackBuffer);
	void Draw();


};

#endif