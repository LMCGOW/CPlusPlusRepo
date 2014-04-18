#include "GameOverScreen.h"

/*
	Constructor. Calls the initialise method.
*/
GameOverScreen::GameOverScreen(){

	Initialise();

}

GameOverScreen::~GameOverScreen(){


}

/*
	Updates the game over screen.
*/
void GameOverScreen::Update(){


}

/*
	Initialises the game over screen.
*/
void GameOverScreen::Initialise(){

	d3dMgr = cD3DManager::getInstance();
	d3dSRMgr = cD3DXSpriteMgr::getInstance();
	screen = d3dMgr->getD3DSurfaceFromFile("Images\\Screens\\gameOver.png");

	replayButtonTex = new cD3DXTexture(d3dMgr->getTheD3DDevice(), "Images\\Screens\\replayButton.png");

	replayButtonPos = D3DXVECTOR3(GameInformation::WINDOWWIDTH / 2 - replayButtonTex->getTWidth()/2, GameInformation::WINDOWHEIGHT / 2, 0);
	SetRect(&replayButton, replayButtonPos.x, replayButtonPos.y, replayButtonPos.x + replayButtonTex->getTWidth(), replayButtonPos.y + replayButtonTex->getTHeight());

	restart = false;
}

/*
	Draws the game over screen background
*/
void GameOverScreen::DrawSurface(LPDIRECT3DSURFACE9 theBackBuffer){

	if(screen!=NULL){

		d3dMgr->updateTheSurface(screen, theBackBuffer);
		d3dMgr->releaseTheBackbuffer(theBackBuffer);

	}

}

/*
	Draws any sprites on the game over screen
*/
void GameOverScreen::Draw(){

	d3dSRMgr->drawSprite(replayButtonTex->getTexture(), NULL, NULL, &replayButtonPos, 0xFFFFFFFF);
	
}

/*
	Draws the final score onto the game over screen
*/
void GameOverScreen::DrawScore(int score){


	RECT scorePos;
	SetRect(&scorePos, 325, 250, 500, 400);

	cD3DXFont* scoreFont = new cD3DXFont(d3dMgr->getTheD3DDevice(), NULL, "Arial");

	char str[50];

	sprintf_s(str, 50, "Final score: %d", score);

	scoreFont->printText(str, scorePos);

}

/*
	Checks if the replay button has been pressed
*/	
void GameOverScreen::ReplayButtonClicked(POINT mouse){

	if(mouse.x > replayButton.left && mouse.x < replayButton.right && mouse.y < replayButton.bottom && mouse.y > replayButton.top){

		restart=true;

	}		

}

/*
	Returns true if restart has been clicked
*/
bool GameOverScreen::Restart(){

	return restart;

}

