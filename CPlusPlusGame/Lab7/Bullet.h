#ifndef _BULLET_H
#define _BULLET_H

#include "GameConstants.h"
#include "GameInformation.h"
#include "cD3DManager.h"
#include "cD3DXSpriteMgr.h"
#include "cD3DXTexture.h"

/*
	CLASS DEFINITION: Bullet class. Handles updating and drawing all of the bullets on screen
*/

class Bullet{

public:

	Bullet(D3DXVECTOR3 playerPosition, int halfPlayerTex); //Constructor
	~Bullet();

	bool IsDead(); //Checks if bullet is dead

	void Update(); //Updates bullet
	void Draw(); //Draws bullet
	void Initialise(D3DXVECTOR3 playerPosition); //Initialises the bullet

	bool Intersects(RECT intersectRect); //Checks for an intersection


private:

	int bulletSpeed;
	D3DXVECTOR3 bulletPosition;
	cD3DXTexture* bulletTexture;

	cD3DManager* d3dMgr;
	cD3DXSpriteMgr* d3dSRMgr;

	RECT bulletRect;


};

#endif