#include "Screen.h"

Screen::Screen(){

}

Screen::Screen(LPDIRECT3DSURFACE9 theScreen){

	d3dMgr = cD3DManager::getInstance();
	screen = theScreen;
}

Screen::~Screen(){

}

void Screen::Update(){

	

}

void Screen::Draw(){

}

void Screen::DrawSurface(LPDIRECT3DSURFACE9 theBackBuffer){

	

}

