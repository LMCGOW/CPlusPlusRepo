#include "GameScreen.h"

/*
	default game screen constructor
*/
GameScreen::GameScreen(){

	Initialise();

}

/*
	game screen destructor
*/
GameScreen::~GameScreen(){

}

/*
	initialises the game screen
*/
void GameScreen::Initialise(){

	d3dMgr = cD3DManager::getInstance();
	screen = d3dMgr->getD3DSurfaceFromFile("Images\\Screens\\game.png");

	enemySpawnRate = 3;
	enemySpawnTime = 3.0f;

	spawnWave = false;
	reload = false;
	outOfBullets=false;

	enemies.clear();
	bullets.clear();

	player = new Ship();

	for(int i = 0; i < 3; i++){

		enemies.push_back(new Enemy());

	}

	outOfBulletsFont = NULL;
	reloadFont = NULL;

	sounds= new cXAudio();

	respawnTimer = new Timer();
	decreaseWaveSpawnTimer = new Timer();
	increaseSpawnRateTimer = new Timer();
	reloadTimer = new Timer();

	scoreFont = new cD3DXFont(d3dMgr->getTheD3DDevice(), NULL, "Sans-Serif");
	SetRect(&scorePos, 10, 40, 200, 70);

	score = 0;
	sprintf_s(scoreStr, 50, "Score: %d", score);

	font = new cD3DXFont(d3dMgr->getTheD3DDevice(), NULL, "Arial");
	SetRect(&bulletsLeftPos, 10, 10, 250, 50);

	bulletsLeft = 10;
	sprintf_s(str, 50, "Bullets left: %d", bulletsLeft);

	gameOver=false;
	bgPlay = true;

	loopBg = new LoopBackground();

	tempWaveIncr = 0;

	timerAnim = new TimerAnim();
}

/*
	Restarts the game by re-initialising all necessary fields
*/
void GameScreen::RestartGame(){

	bulletsLeft = 10;
	score = 0;

	enemies.clear();
	bullets.clear();

	enemySpawnRate = 3;
	enemySpawnTime = 3.0f;

	spawnWave = false;
	reload = false;
	outOfBullets=false;

	respawnTimer = new Timer();
	decreaseWaveSpawnTimer = new Timer();
	increaseSpawnRateTimer = new Timer();
	reloadTimer = new Timer();
	timerAnim = new TimerAnim();

	player = new Ship();

	for(int i = 0; i < 3; i++){

		enemies.push_back(new Enemy());

	}

	gameOver = false;
	


}

/*
	updates the game screen and associated objects
*/
void GameScreen::FixedUpdate(){

	
}


/*
	Updates the game screen and associated objects
*/
void GameScreen::Update(){

	//If game over is false
	if(!gameOver){

		//Loop the background
		loopBg->Loop();

		//Play the music 
		if(bgPlay){

			sounds->playSound(L"Sounds\\bg.wav", true);
			bgPlay=false;

		}

		//Update player and timer anim
		player->Update();
		timerAnim->UpdateTimer();

		//Updates all enemies
		for(enemyIter = enemies.begin(); enemyIter != enemies.end(); ++enemyIter){

			(*enemyIter)->Update();

			}

		//Updates all bullets
		for(bulletIter = bullets.begin(); bulletIter != bullets.end(); ++bulletIter){

			(*bulletIter)->Update();

		}

		//If GameOver method in TimerAnim class returns true, then set gameOver to true
		if(timerAnim->GameOver())
			gameOver = true;

	}


		//Updates the score and bullet strings
		sprintf_s(scoreStr, 50, "Score: %d", score);
		sprintf_s(str, 50, "Bullets left: %d", bulletsLeft);

		//If the bullet is to be reloaded
		if(reload){
			//Add one bullet after 0.2 seconds left
			if(reloadTimer->TimePassed(0.2f)){
				bulletsLeft+=1;
			}

			//If bullets are back at ten, stop reloading
			if(bulletsLeft>=10){
				bulletsLeft=10;
				reload=false;
			}
		}

		//If no bullets left, set outOfBullets = true
		if(bulletsLeft <=0){
			outOfBullets=true;
		}else{
			outOfBullets=false;
		}
	
		//Call necessary methods
		SpawnEnemyWave();
		IncreaseSpawnRate();
		DisposeOfDeadObjects();
		CheckForBulletEnemyCollision();
		CheckForEnemyPlayerCollision();

	

}

/*
	Checks for enemy player collision
*/
void GameScreen::CheckForEnemyPlayerCollision(){

	//Loops through enemy list
	for(enemyIter=enemies.begin();enemyIter!=enemies.end();++enemyIter){

		//If the enemy collided with has not exploded
		RECT r;
		if(!(*enemyIter)->Exploded()){

			//If there is an intersection between an enemy and player
			if(IntersectRect(&r, &(*enemyIter)->GetRect(), &player->GetBoundingRect())){

				//End game
				gameOver=true;

			}

		}

	}

}

/*
	returns true if game over
*/
bool GameScreen::GameOver(){

	return gameOver;

}

/*
	Checks for bullet and enemy collision.
*/
void GameScreen::CheckForBulletEnemyCollision(){

	//Loops through enemy list
	for(enemyIter = enemies.begin(); enemyIter != enemies.end(); enemyIter++){

		//Loops through bullet list
		for(bulletIter = bullets.begin(); bulletIter != bullets.end(); bulletIter++){

			//If the enemy is not exploding and an intersection has occurred
			if(!(*enemyIter)->Exploded()){
			if((*bulletIter)->Intersects((*enemyIter)->GetRect())){

				tempWaveIncr++; //increase tempWaveIncr
				sounds->playSound(L"Sounds\\explosion_single_large_09.wav", false); //Play the explosion sound
				bulletIter = bullets.erase(bulletIter); //Erase the bullet 
				(*enemyIter)->SetExploding(); //Explode the enemy
				IncreaseScore(); //Increase the score
				return; 

			}
			}

		}

	}

}

/*
	handles game screen input and associated objects
*/
void GameScreen::HandleInput(WPARAM wParam, string keyState){
	
	//Invokes the handle input method of the player
	player->HandleInput(wParam, keyState);

	//If "r" key is pressed, reload
	if(wParam=='R'){
	
		reload=true;

	}
}

/*
	draws the game screen and associated objects
*/
void GameScreen::Draw(){

	//Draws the backgrounds
	loopBg->DrawBackgrounds();

	//Draws the player stuff
	player->Draw();
	
	//Loops through enemies list and draws the enemies
	for(enemyIter = enemies.begin(); enemyIter != enemies.end(); ++enemyIter){

		(*enemyIter)->Draw();

	}

	//Loops through bullet list and draws the bullets
	for(bulletIter = bullets.begin(); bulletIter != bullets.end(); ++bulletIter){

		(*bulletIter)->Draw();

	}

	//Draws the timer animation
	timerAnim->Draw();

}

/*
	draws the game screen surface
*/
void GameScreen::DrawSurface(LPDIRECT3DSURFACE9 theBackBuffer){

	//If screen is not null then
	if(screen!=NULL){

		//Update the surface and release the back buffer
		d3dMgr->updateTheSurface(screen, theBackBuffer);
		d3dMgr->releaseTheBackbuffer(theBackBuffer);

	}

}

/*
	will spawn a new wave of enemies every 7 seconds
*/
void GameScreen::SpawnEnemyWave(){

	//If enemySpawnTime has passed then
	if(respawnTimer->TimePassed(enemySpawnTime)){

		//Loop until enemy spawn rate has been reached and
		for(int i = 0; i < enemySpawnRate; i++){

			//Create new enemies
			enemies.push_back(new Enemy());

		}
	}

}

/*
	decreases the spawn timer after 15 seconds
*/
void GameScreen::DecreaseSpawnTimer(){

	//If 60 seconds have passed then reduce the enemy spawn time
	if(decreaseWaveSpawnTimer->TimePassed(60.0f))
		enemySpawnTime -= 0.1f;

}

/*
	increases spawn rate after 10 seconds
*/
void GameScreen::IncreaseSpawnRate(){

	//If player has 15 points then
	if(tempWaveIncr >= 15){

		//Set tempWaveIncr back to 1
		tempWaveIncr = 1;
		enemySpawnRate++;

	}

}

/*
	will dispose of any enemies that die
*/
void GameScreen::DisposeOfDeadObjects(){

	//Loops through enemies and erases if they're dead
	for(enemyIter = enemies.begin(); enemyIter != enemies.end(); ++enemyIter){

		if((*enemyIter)->IsDead()){

			enemyIter = enemies.erase(enemyIter);

		}

	}

	//Loops through bullets and erases if they're dead
	for(bulletIter=bullets.begin(); bulletIter!=bullets.end();++bulletIter){

		if((*bulletIter)->IsDead()){
			bulletIter=bullets.erase(bulletIter);
		
		}

	}



}

/*
	Returns the score.
*/
int GameScreen::GetScore(){

	return score;

}

/*
	Creates a bullet 
*/
void GameScreen::CreateBullet(){

	//If you are not reloading, and you have bullets left
	if(bulletsLeft>0 && !reload){

		sounds->playSound(L"Sounds\\beam_start.wav", false); //Play sound
		int halfPlayerTex = player->GetTexture()->getTWidth() / 2; 
		bullets.push_back(new Bullet(player->GetPosition(), halfPlayerTex)); //Create bullet
		DecreaseBullets(); //Reduce number of bullets 

	}
	 
	//Ensures bullets cannot go below zero
	if(bulletsLeft<0)
		bulletsLeft=0;

	
}

/*
	Decreases the bullets by 1 every time this method is invoked.
*/
void GameScreen::DecreaseBullets(){

	bulletsLeft-=1;

}

/*
	This handles drawing text to the screen.
*/
void GameScreen::DrawTextScreen(){

	scoreFont->printText(scoreStr, scorePos);
	font->printText(str, bulletsLeftPos);

	if(reload){

		if(reloadFont == NULL){

			reloadFont = new cD3DXFont(d3dMgr->getTheD3DDevice(), NULL, "Arial");
			RECT reloadRect;

			SetRect(&reloadRect, (GameInformation::WINDOWWIDTH - 150), (GameInformation::WINDOWHEIGHT - 40), 900, (GameInformation::WINDOWHEIGHT - 10));
		}

		reloadFont->printText("Reloading...", reloadRect);

	}

	if(outOfBullets){

		if(outOfBulletsFont == NULL){

		outOfBulletsFont = new cD3DXFont(d3dMgr->getTheD3DDevice(), NULL, "Arial");
		SetRect(&routOfBullets, 320, 200, 500, 410);
		SetRect(&r2outOfBullets, 287, 250, 550, 460);

		}

		outOfBulletsFont->printText("Out of Bullets!", routOfBullets);
		outOfBulletsFont->printText("Press 'R' to Reload.", r2outOfBullets);

	}
	

}

/*
	Increases score by 1
*/
void GameScreen::IncreaseScore(){

	score+=1;

}



