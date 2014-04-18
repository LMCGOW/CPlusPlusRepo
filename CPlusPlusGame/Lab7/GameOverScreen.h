#include "GameConstants.h"
#include "cD3DManager.h"
#include "cD3DXSpriteMgr.h"
#include "cD3DXTexture.h"
#include "GameInformation.h"
#include "cD3DXFont.h"

/*
	CLASS DEFINITION: Handles drawing and updating game over screen
*/

class GameOverScreen{

private:

	LPDIRECT3DSURFACE9 screen;
	cD3DManager* d3dMgr;
	cD3DXSpriteMgr* d3dSRMgr;

	cD3DXTexture* replayButtonTex;

	int score;
	RECT scorePos;
	cD3DXFont* scoreFont;
	char str[50];

	bool restart;

public:

	GameOverScreen(); //Default constructor
	~GameOverScreen(); //Default destructor

	void Update(); //Updates the game over screen
	void DrawSurface(LPDIRECT3DSURFACE9 theBackBuffer); //Draws screen
	void Draw(); //Draws all stuff on screen
	void Initialise(); //Initialises the screen
	bool Restart(); //Restarts the game

	void DrawScore(int score); //Draws the end score on screen
	
	void ReplayButtonClicked(POINT mouse); //Checks if the replay button has been clicked

	cD3DXTexture* playButtonTex;
	D3DXVECTOR3 replayButtonPos;
	RECT replayButton;





};
