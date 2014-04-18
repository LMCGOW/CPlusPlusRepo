#ifndef _ENEMY_H
#define _ENEMY_H

#include "GameConstants.h"
#include "cD3DXSpriteMgr.h"
#include "cD3DXTexture.h"
#include "cD3DManager.h"
#include "RandomNumber.h"
#include "Timer.h"
#include "GameInformation.h"
#include "Ship.h"

/*
	CLASS DEFINITION: Enemy class - handles updating and drawing all enemies on screen
*/

class Enemy{

private:

	D3DXVECTOR3 enemyPosition;

	float enemySpeed;
	float maxEnemySpeed;
	float minEnemySpeed;

	//The d3d manager
	cD3DManager* d3dMgr;
	cD3DXSpriteMgr* spriteManager;

	//The ship texture
	cD3DXTexture* enemyTextures[5];
	int currentFrame;
	char path[50];

	Timer* explosionTimer;
	bool exploding;
	bool exploded;

	RandomNumber* randomNumber;

	RECT enemyRect;

	void Initialise();

	D3DXVECTOR2 centre;
	int radius;

	BoundingBox* box;

public:

	Enemy(); //Default constructor
	~Enemy(); //Default destructor

	void Update(); //Updates enemy
	void Draw(); //Draws enemy

	void HandleInput(WPARAM wParam); //Handles input for the enemy

	bool IsDead(); //Checks if the enemy is dead

	RECT GetRect(); //Returns the bounding rect for the enemy

	
	void SetPosition(); //Sets the enemy position

	void ExplodeEnemy(); //Explodes enemy
	void SetExploding(); //Sets if enemy is exploding
	bool FinishedExploding(); //Checks if finished exploding
	bool IsExploding(); //Returns true if is exploding
	bool Exploded(); //Returns true if has exploded

};
#endif