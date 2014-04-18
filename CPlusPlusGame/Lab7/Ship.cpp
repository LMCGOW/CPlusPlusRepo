#include "Ship.h"

/*
	default ship constructor
*/
Ship::Ship(){

	Initialise();

}

/*
	intialises the ship class
*/
void Ship::Initialise(){

	d3dMgr = cD3DManager::getInstance();
	spriteManager = cD3DXSpriteMgr::getInstance();

	shipTexture = new cD3DXTexture(d3dMgr->getTheD3DDevice(), "Images\\ship.png");

	shipSpeed = D3DXVECTOR2(10, 10);
	shipPosition = D3DXVECTOR3(50, ((GameInformation::WINDOWHEIGHT - shipTexture->getTHeight()) - 20), 0);

	box = new BoundingBox();

	bullets = 0;

	up=down=left=right=false;

}


/*
	handles updating the logic for the Ship class
*/
void Ship::Update(){

	CheckWithinBounds();
	
	SetRect(&shipRect, shipPosition.x, shipPosition.y, shipTexture->getTWidth() + shipPosition.x, shipTexture->getTHeight() + shipPosition.y);

	box->SetPositions(shipRect.left, shipRect.top, shipRect.left, shipRect.top, shipRect.right, shipRect.top, shipRect.left, shipRect.bottom);

	if(right){
		shipPosition.x += shipSpeed.x;
	}

	if(left){
		shipPosition.x -= shipSpeed.x;
	}
}

RECT Ship::GetBoundingRect(){

	return shipRect;

}

/*
	ensures the ship stays within the bounds of the window
*/
void Ship::CheckWithinBounds(){

	if(shipPosition.x < 0)
		shipPosition.x = 0;

	if((shipPosition.x + shipTexture->getTWidth()) > GameInformation::WINDOWWIDTH){

		shipPosition.x = GameInformation::WINDOWWIDTH - shipTexture->getTWidth();

	}

}

/*
	will handle the input for the Ship class
*/
void Ship::HandleInput(WPARAM wParam, string keyState){

	
	if(wParam == 'A' && keyState=="pressed"){
		left=true;
		right=false;
	}

	else if(wParam=='D' && keyState=="pressed"){
		right=true;
		left=false;
	}

	if(wParam=='A' && keyState == "released"){
		left=false;
	}else if(wParam=='D' && keyState=="released"){
		right=false;
	}


}

/*
	Returns the ship position
*/
D3DXVECTOR3 Ship::GetPosition(){

	return shipPosition;

}

/*
	Returns the ship texture
*/
cD3DXTexture* Ship::GetTexture(){

	return shipTexture;

}

/*
	handles drawing within the Ship class
*/
void Ship::Draw()
{

	box->Draw();
	spriteManager->drawSprite(shipTexture->getTexture(), NULL, NULL, &shipPosition, 0xFFFFFFFF);

}