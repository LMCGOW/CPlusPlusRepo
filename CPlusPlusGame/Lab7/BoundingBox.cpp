#include "BoundingBox.h"

/*
	Constructor. Initialises all of the necessary instance fields.
*/
BoundingBox::BoundingBox(int xtop, int ytop, int xleft, int yleft, int xright, int yright, int xbot, int ybot){

	m_pD3DMgr = cD3DManager::getInstance();
	m_pD3DSRMgr = cD3DXSpriteMgr::getInstance();

	m_xtop = xtop;
	m_ytop = ytop;
	m_xleft = xleft;
	m_yleft = yleft;
	m_xright = xright;
	m_yright = yright;
	m_xbot = xbot;
	m_ybot = ybot;


		horizTex = new cD3DXTexture(m_pD3DMgr->getTheD3DDevice(), "Images\\boxH.png");
		verTex = new cD3DXTexture(m_pD3DMgr->getTheD3DDevice(), "Images\\boxV.png");

}

/*
	Default constructor
*/
BoundingBox::BoundingBox(){

	m_pD3DMgr = cD3DManager::getInstance();
	m_pD3DSRMgr = cD3DXSpriteMgr::getInstance();

	horizTex = new cD3DXTexture(m_pD3DMgr->getTheD3DDevice(), "Images\\boxH.png");
	verTex = new cD3DXTexture(m_pD3DMgr->getTheD3DDevice(), "Images\\boxV.png");

}

/*
	Sets positions if necessary.
*/
void BoundingBox::SetPositions(int xtop, int ytop, int xleft, int yleft, int xright, int yright, int xbot, int ybot){

	m_xtop = xtop;
	m_ytop = ytop;
	m_xleft = xleft;
	m_yleft = yleft;
	m_xright = xright;
	m_yright = yright;
	m_xbot = xbot;
	m_ybot = ybot;

}

BoundingBox::~BoundingBox(){



}

/*
	Draws the bounding box (each line individually)
*/
void BoundingBox::Draw(){

	m_pD3DSRMgr->drawSprite(horizTex->getTexture(), NULL, NULL, &D3DXVECTOR3(m_xtop, m_ytop, 0), 0xFFFFFFFF);
	m_pD3DSRMgr->drawSprite(horizTex->getTexture(), NULL, NULL, &D3DXVECTOR3(m_xbot, m_ybot, 0), 0xFFFFFFFF);
	m_pD3DSRMgr->drawSprite(verTex->getTexture(), NULL, NULL, &D3DXVECTOR3(m_xleft, m_yleft, 0), 0xFFFFFFFF);
	m_pD3DSRMgr->drawSprite(verTex->getTexture(), NULL, NULL, &D3DXVECTOR3(m_xright, m_yright, 0), 0xFFFFFFFF);

}