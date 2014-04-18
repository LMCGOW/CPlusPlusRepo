#include "ScreenManager.h"

ScreenManager* ScreenManager::instance = NULL;

 /*
	Screen manager constructor
 */
ScreenManager::ScreenManager()
{

	activeScreen = Menu; //Sets the initial screen

	menuScreen = MenuScreen();
	gameScreen = GameScreen();
	gameOver=GameOverScreen();
	instructions = InstructionsScreen();

}

/*
	updates the current screen
*/
void ScreenManager::Update()
{

	switch(activeScreen){

	case Menu:
		menuScreen.Update();
		break;
	case Game:
		gameScreen.Update();
		break;
	}

	if(gameScreen.GameOver())
		SetActiveScreen(GameOver);

	RestartGame();

}


/*
	draws the current screen
*/
void ScreenManager::DrawSurface(LPDIRECT3DSURFACE9 theBackbuffer)
{
	
	switch(activeScreen){

	case Menu:
		menuScreen.DrawSurface(theBackbuffer);
		break;
	case Game:
		gameScreen.DrawSurface(theBackbuffer);
		break;
	case GameOver:
		gameOver.DrawSurface(theBackbuffer);
		break;
	case Instructions:
		instructions.DrawSurface(theBackbuffer);
		break;
	}

}

/*
	Draws any sprites necessary in the current screen
*/
void ScreenManager::Draw(){

	switch(activeScreen){

	case Menu:
		menuScreen.Draw();
		break;
	case Game:
		gameScreen.Draw();
		break;
	case GameOver:
		gameOver.Draw();
		gameOver.DrawScore(gameScreen.GetScore());
		break;

	}

}

/*
	Passes input information into the screens
*/
void ScreenManager::HandleInput(WPARAM wParam, string keyState){

	switch(activeScreen){

	case Menu:
		menuScreen.HandleInput(wParam, keyState);
		break;
	case Game:
		gameScreen.HandleInput(wParam, keyState);
		break;
	case Instructions:

		if(wParam == 'G'){
			activeScreen = Game;
		}

	}

}

/*
	sets the active screen index
*/
void ScreenManager::SetActiveScreen(Screens active)
{

	activeScreen= active;

}

/*
	returns the active screen
*/
Screens ScreenManager::ReturnActiveScreen()
{

	return activeScreen;

}

/*
	Checks for a keyboard press and responds accordingly
*/
void ScreenManager::KeyboardPressed(){

	if(activeScreen == Game){
		gameScreen.CreateBullet();
	}

}

/*
	Draws necessary text on the necessary screens
*/
void ScreenManager::DrawTextScreen(){

	if(activeScreen==Game){
		gameScreen.DrawTextScreen();
	}

}

/*
	Checks if left mouse button is clicked and handles accordingly
*/
void ScreenManager::LeftButtonClicked(POINT mouse){

	if(activeScreen == Menu){

		if(menuScreen.PlayButtonClicked(mouse)){
			activeScreen = Instructions;
		};

	}

	if(activeScreen==GameOver){
		gameOver.ReplayButtonClicked(mouse);
	}

	
	if(activeScreen == Game){
		gameScreen.CreateBullet();
	}
}

/*
	Returns the instance
*/
ScreenManager* ScreenManager::GetInstance(){

	if(instance == NULL)
		instance = new ScreenManager();

	return instance;

}

/*	
	Restarts the game
*/
void ScreenManager::RestartGame(){

	if(activeScreen==GameOver){

		if(gameOver.Restart()){

			gameScreen.RestartGame();
			gameOver = GameOverScreen();

			activeScreen=Game;
		}
	}

}