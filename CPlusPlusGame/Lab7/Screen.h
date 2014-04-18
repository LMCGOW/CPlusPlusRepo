#ifndef _SCREEN_H
#define _SCREEN_H

#include "GameConstants.h"
#include "cD3DManager.h"
#include "cD3DXSpriteMgr.h"

class Screen{

protected:

	LPDIRECT3DSURFACE9 screen; //The screen that will be drawn
	cD3DManager* d3dMgr; //The d3d manager
	cD3DXSpriteMgr* d3dSRMgr; //The sprite manager

private:

	
	

public:

	Screen();
	Screen(LPDIRECT3DSURFACE9 theScreen);
	~Screen(); //Destructor

	void Update();
	void Draw();
	virtual void DrawSurface(LPDIRECT3DSURFACE9 theBackBuffer);

};
#endif