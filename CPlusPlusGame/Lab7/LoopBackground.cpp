#include "LoopBackground.h"

LoopBackground::LoopBackground(){

	Initialise();

}

LoopBackground::~LoopBackground(){



}

/*
	Initialises the class.
*/
void LoopBackground::Initialise(){

	d3dMgr = cD3DManager::getInstance();
	d3dSRMgr = cD3DXSpriteMgr::getInstance();

	bg1 = new cD3DXTexture(d3dMgr->getTheD3DDevice(), "Images\\Screens\\bg.png");
	bg2 = new cD3DXTexture(d3dMgr->getTheD3DDevice(), "Images\\Screens\\bg1.png");

	bg1pos = D3DXVECTOR3(0, 0, 0);
	bg2pos = D3DXVECTOR3(0, -600, 0);

}

/*
	Moves the background and loops it.
*/
void LoopBackground::Loop(){

	bg1pos.y+=2;
	bg2pos.y+=2;

	if(bg1pos.y >= 600)
		bg1pos.y = -600;

	if(bg2pos.y >= 600)
		bg2pos.y = -600;

}

/*
	Draws the background.
*/
void LoopBackground::DrawBackgrounds(){

	d3dSRMgr->drawSprite(bg1->getTexture(), NULL, NULL, &bg1pos, 0xFFFFFFFF);
	d3dSRMgr->drawSprite(bg2->getTexture(), NULL, NULL, &bg2pos, 0xFFFFFFFF);

}