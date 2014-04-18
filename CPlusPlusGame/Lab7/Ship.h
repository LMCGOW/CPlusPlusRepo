/*
=================
Ship.h
- Header file for class definition - SPECIFICATION
- Header file for the Ship class
=================
*/

#ifndef _SHIP_H
#define _SHIP_H
#include "GameConstants.h"
#include "cD3DXTexture.h"
#include "cD3DXSpriteMgr.h"
#include "cD3DManager.h"
#include "GameInformation.h"
#include "DirectInputHandler.h"
#include "Timer.h"
#include "BoundingBox.h"

/*
	CLASS DEFINITION: Handles updating and drawing the ship
*/

class Ship{

private:

	//The position and speed of the ship
	D3DXVECTOR3 shipPosition;
	D3DXVECTOR2 shipSpeed;

	//The d3d manager
	cD3DManager* d3dMgr;
	cD3DXSpriteMgr* spriteManager;

	//The ship texture
	cD3DXTexture* shipTexture;

	RECT shipRect;

	BoundingBox* box;

	int bullets;

	bool up;
	bool down;
	bool left;
	bool right;

public:

	Ship(); //Default constructor
	~Ship(); //Destructor

	void Update(); //Update method
	void Draw(); //Draw method
	void HandleInput(WPARAM wParam, string keyState); //Controls input
	void Initialise(); //Initialises the ship
	void CheckWithinBounds(); //Keeps the ship inside the bounds of the window

	D3DXVECTOR3 GetPosition(); //Returns the position
	cD3DXTexture* GetTexture(); //Returns the texture
	RECT GetBoundingRect(); //Returns the bounding rectangle
	
};
#endif