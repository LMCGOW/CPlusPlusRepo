#include "TimerAnim.h"

/*
	Default constructor.
*/
TimerAnim::TimerAnim(){

	Initialise();

}

/*
	Destructor.
*/
TimerAnim::~TimerAnim(){



}

/*
	Initialises the object.
*/
void TimerAnim::Initialise(){

	d3dMgr = cD3DManager::getInstance();
	d3dSRMgr = cD3DXSpriteMgr::getInstance();

	currFrame = 0;
	
	for(int i=0; i < 16; i++){

		sprintf_s(path, 50, "Images\\SprayTextures\\sprayRemainingFULL%d.png", i);
		sprayTextures[i] = new cD3DXTexture(d3dMgr->getTheD3DDevice(), path);

	}

	gameTimer = new Timer();

}

/*
	Updates timer.
*/
void TimerAnim::UpdateTimer(){

	if(gameTimer->TimePassed(11.25f)){
		currFrame++;
	}


}

/*
	Called when a frame should be changed
*/
void TimerAnim::ChangeFrame(){

	currFrame++;

}

/*
	Draws the timer sprite
*/
void TimerAnim::Draw(){

	if(currFrame <= 15){
		d3dSRMgr->drawSprite(sprayTextures[currFrame]->getTexture(), NULL, NULL, &D3DXVECTOR3(GameInformation::WINDOWWIDTH - 130, 10, 0), 0xFFFFFFFF);
	}

}

/*
	Returns true if the timer animation has reached its last frame and thus ended.
*/
bool TimerAnim::GameOver(){

	if(currFrame >= 15)
		return true;

		return false;


}