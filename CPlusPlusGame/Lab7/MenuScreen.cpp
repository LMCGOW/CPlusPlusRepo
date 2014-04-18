#include "MenuScreen.h"

/*
	Constructor. Calls the initialise method
*/
MenuScreen::MenuScreen(){

	Initialise();

}

void MenuScreen::Update(){

	

}

void MenuScreen::HandleInput(WPARAM wParam, string keyState){



}

/*
	Initialises the menu screen variables
*/
void MenuScreen::Initialise(){

	d3dMgr = cD3DManager::getInstance();
	d3dSRMgr = cD3DXSpriteMgr::getInstance();
	screen = d3dMgr->getD3DSurfaceFromFile("Images\\Screens\\menu.png");

	playButtonTex = new cD3DXTexture(d3dMgr->getTheD3DDevice(), "Images\\Screens\\playButton.png");

	playButtonPos = D3DXVECTOR3(GameInformation::WINDOWWIDTH / 2 - playButtonTex->getTWidth()/2, GameInformation::WINDOWHEIGHT / 2 - GameInformation::WINDOWHEIGHT / 5, 0);
	SetRect(&playButton, playButtonPos.x, playButtonPos.y, playButtonPos.x + playButtonTex->getTWidth(), playButtonPos.y + playButtonTex->getTHeight());


}

//Draws play button
void MenuScreen::Draw(){

	SetRect(&playButton, playButtonPos.x, playButtonPos.y, playButtonPos.x + playButtonTex->getTWidth(), playButtonPos.y + playButtonTex->getTHeight());
	d3dSRMgr->drawSprite(playButtonTex->getTexture(), NULL, NULL, &playButtonPos, 0xFFFFFFFF);
	
}

//Draws screen 
void MenuScreen::DrawSurface(LPDIRECT3DSURFACE9 theBackBuffer){

	if(screen!=NULL){

		d3dMgr->updateTheSurface(screen, theBackBuffer);
		d3dMgr->releaseTheBackbuffer(theBackBuffer);

	}
}

/*
	returns true if play button is clicked
*/
bool MenuScreen::PlayButtonClicked(POINT mouse){

	if(mouse.x > playButton.left && mouse.x < playButton.right && mouse.y < playButton.bottom && mouse.y > playButton.top){

		return true;

	}else

		return false;

}
