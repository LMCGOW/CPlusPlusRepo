#include "InstructionsScreen.h"

InstructionsScreen::InstructionsScreen(){

	Initialise();

}

InstructionsScreen::~InstructionsScreen(){

}

void InstructionsScreen::Initialise(){

	d3dMgr = cD3DManager::getInstance();
	d3dSRMgr = cD3DXSpriteMgr::getInstance();

	screen = d3dMgr->getD3DSurfaceFromFile("Images\\Screens\\instructions.png");

}

void InstructionsScreen::Draw(){



}


void InstructionsScreen::DrawSurface(LPDIRECT3DSURFACE9 theBackBuffer){

	//If screen is not null then
	if(screen!=NULL){

		//Update the surface and release the back buffer
		d3dMgr->updateTheSurface(screen, theBackBuffer);
		d3dMgr->releaseTheBackbuffer(theBackBuffer);

	}

}