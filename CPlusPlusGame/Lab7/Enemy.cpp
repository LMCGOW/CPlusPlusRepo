#include "Enemy.h"
#include <string>

/*
	Default constructor. Initialises the enemy by calling the initialise method.
*/
Enemy::Enemy(){

	Initialise();

}

/*
	destructor
*/
Enemy::~Enemy(){



}

/*
	intialises the enemy
*/
void Enemy::Initialise(){

	//An object of a custom random number class.
	randomNumber = RandomNumber::GetInstance();

	minEnemySpeed = 3;
	maxEnemySpeed = 5;

	enemyPosition = D3DXVECTOR3(randomNumber->GenerateRandomNumber(800), 0, 0);

	d3dMgr = cD3DManager::getInstance();
	spriteManager = cD3DXSpriteMgr::getInstance();

	currentFrame = 0;

	//Gets the correct paths for the enemy frames and stores them in the array
	for(int i = 0; i < 5; i++){

		sprintf_s(path, 50, "Images\\EnemySprites\\enemyFrame%d.png", i);
		enemyTextures[i] = new cD3DXTexture(d3dMgr->getTheD3DDevice(), path);

	}

	//Exploding variables
	exploding = false;
	exploded=false;

	//An object of a custom timer class
	explosionTimer = new Timer();

	//Sets the enemy speed
	while(enemySpeed < minEnemySpeed){
		enemySpeed = randomNumber->GenerateRandomNumber(maxEnemySpeed);
	}

	//Instantiates the bounding box object
	box = new BoundingBox();

}

/*
	updates the enemy
*/
void Enemy::Update(){

	//If the enemy is not exploding, update as normal
	if(!exploding){

		enemyPosition.y+= enemySpeed;

		//Bounds the enemy to the window
		#pragma region
		if(enemyPosition.x < 0)
			enemyPosition.x = 0;

		if((enemyPosition.x + enemyTextures[0]->getTWidth()) > GameInformation::WINDOWWIDTH){

			enemyPosition.x = GameInformation::WINDOWWIDTH - enemyTextures[0]->getTWidth();

		}
		#pragma endregion BoundToWindow

		//Sets the bounding rectangle every frame
		SetRect(&enemyRect, enemyPosition.x, enemyPosition.y, enemyPosition.x + enemyTextures[0]->getTWidth(), enemyPosition.y + enemyTextures[0]->getTHeight());
		
		//Sets the drawn bounding box
		box->SetPositions(enemyRect.left, enemyRect.top, enemyRect.left, enemyRect.top, enemyRect.right, enemyRect.top, enemyRect.left, enemyRect.bottom);
	}

	//If it is exploding, play exploding animation
	if(exploding)
		ExplodeEnemy();


}

/*
	Animates the explosion
*/
void Enemy::ExplodeEnemy(){

	//Invokes the custom Timer method "TimePassed" in order to check if 0.05 of a second has passed
	if(explosionTimer->TimePassed(0.05f)){

		//If we are at the final frame of animation, stop exploding
		if(currentFrame>=4)
			exploding=false;

		//Add one to current frame
		currentFrame+=1;

	}

}

/*
	draws the enemy
*/
void Enemy::Draw(){

	//Draw the enemy and the bounding box if we are not beyond the last frame
	if(currentFrame<=4){
	box->Draw();
	spriteManager->drawSprite(enemyTextures[currentFrame]->getTexture(), NULL, NULL, &enemyPosition, 0xFFFFFFFF);
	}

}

/*
	will return true if the enemy has been shot or has made it off screen
*/
bool Enemy::IsDead(){

	if(enemyPosition.y > GameInformation::WINDOWHEIGHT){

		return true;

	}

	else

		return false;

}

/*
	Returns the bounding box
*/
RECT Enemy::GetRect(){

	return enemyRect;

}

//Sets the enemy to exploding
void Enemy::SetExploding(){
	exploding=true;
	exploded=true;
}

//Returns false if the enemy has finished exploding
bool Enemy::FinishedExploding(){

	return exploding;

}

//Returns true if the enemy has exploded
bool Enemy::Exploded(){
	return exploded;
}

