#ifndef _GAMESCREEN_H
#define _GAMESCREEN_H

#include "Ship.h"
#include "Enemy.h"
#include "Timer.h"
#include "Bullet.h"
#include "cD3DXFont.h"
#include "cD3DManager.h"
#include "cXAudio.h"
#include "LoopBackground.h"
#include "TimerAnim.h"

/*
	CLASS DEFINITION: Draws and updates the game screen
*/

class GameScreen{

private:

	cD3DManager* d3dMgr;

	LPDIRECT3DSURFACE9 screen;
	Ship* player;
	
	vector<Enemy*> enemies;
	vector<Enemy*>::iterator enemyIter;

	vector<Bullet*> bullets;
	vector<Bullet*>::iterator bulletIter;

	int enemySpawnRate;
	float enemySpawnTime;
	bool spawnWave;

	bool outOfBullets;
	bool reload;
	bool exploding;

	Timer* respawnTimer;
	Timer* decreaseWaveSpawnTimer;
	Timer* increaseSpawnRateTimer;
	Timer* reloadTimer;

	TimerAnim* timerAnim; //The timer animation object

	int tempWaveIncr; //This is incrememnted every time the player gets a point, and then once it reaches five, the enemy spawn rate is increased and this is reset back to 1

	vector<Enemy*> GetEnemies();

	int bulletsLeft;
	RECT bulletsLeftPos;
	cD3DXFont* font;
	char str[50];

	int score;
	RECT scorePos;
	cD3DXFont* scoreFont;
	char scoreStr[50];

	cXAudio* sounds;

	bool gameOver;

	bool bgPlay;

	cD3DXFont* outOfBulletsFont;
	RECT routOfBullets;
	RECT r2outOfBullets;

	cD3DXFont* reloadFont;
	RECT reloadRect;

	LoopBackground* loopBg;
	
	

public:

	GameScreen(); //Default constructor
	~GameScreen(); //Default destructor

	void Update(); //Updates game screen
	void Draw(); //Draws game screen
	void DrawSurface(LPDIRECT3DSURFACE9 theBackBuffer); //Draws game screen surface
	void Initialise(); //Initialises game screen
	void HandleInput(WPARAM wParam, string keyState); //Handles game screen logic
	void SpawnEnemyWave(); //Spawns enemy waves
	void DecreaseSpawnTimer(); //Decreases spawn timer
	void IncreaseSpawnRate(); //Increase spawn rate
	void DisposeOfDeadObjects(); //Destroys objects that are dead
	void CreateBullet(); //Creates bullet
	void CheckForBulletEnemyCollision(); //Checks for bullet and enemy collision
	void CheckForEnemyPlayerCollision(); //Checks for enemy and player collision
	void DecreaseBullets(); //Decrease bullets
	void DrawTextScreen(); //Draws text on screen
	void IncreaseScore(); //Increase score
	void FixedUpdate();
	void RestartGame(); //Restarts the game

	bool GameOver(); //Checks if the game is over

	int GetScore(); //Returns the score



};
#endif