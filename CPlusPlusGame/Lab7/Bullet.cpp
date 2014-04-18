#include "Bullet.h"

/*
	Constructor. Calls the initialise method.
*/
Bullet::Bullet(D3DXVECTOR3 playerPosition, int halfPlayerTex){


	Initialise(playerPosition);

}

Bullet::~Bullet(){


}

/*
	Initialises the bullet class.
*/
void Bullet::Initialise(D3DXVECTOR3 playerPosition){

	d3dMgr = cD3DManager::getInstance();
	d3dSRMgr = cD3DXSpriteMgr::getInstance();

	bulletPosition = playerPosition;
	bulletTexture = new cD3DXTexture(d3dMgr->getTheD3DDevice(), "Images\\bullet.png");

	bulletSpeed = 20;

}

/*
	updates the bullet
*/
void Bullet::Update(){

	bulletPosition.y -= bulletSpeed;

	//Sets the bounding rect of the bullet
	SetRect(&bulletRect, bulletPosition.x, bulletPosition.y, bulletTexture->getTWidth() + bulletPosition.x, bulletTexture->getTHeight() + bulletPosition.y);

}

/*
	returns true if the bullet goes off screen
*/
bool Bullet::IsDead(){

	if(bulletPosition.y > (GameInformation::WINDOWHEIGHT + 100)){

		return true;

	}

	else

		return false;

}

/*
	will draw the bullet
*/
void Bullet::Draw(){

	d3dSRMgr->drawSprite(bulletTexture->getTexture(), NULL, NULL, &bulletPosition, 0xFFFFFFFF);	

}

//If the bullet intersects the passed in rectangle, true will be returned
bool Bullet::Intersects(RECT intersectRect){

	
	if(bulletPosition.x > intersectRect.left && bulletPosition.x < intersectRect.right && bulletPosition.y < intersectRect.bottom && bulletPosition.y > intersectRect.top){
		return true;
	}else
		return false;
		

}

