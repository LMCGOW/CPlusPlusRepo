#include "cD3DManager.h"
#include "cD3DXSpriteMgr.h"
#include "cD3DXTexture.h"

/*
	CLASS DEFINITION: creates and draws a bounding box around all objects that use this class
*/

class BoundingBox{

public:

	BoundingBox(); //Default constructor
	BoundingBox(int xtop, int ytop, int xleft, int yleft, int xright, int yright, int xbot, int ybot); //Default constructor that sets the bounding box dimensions (for static objects)
	~BoundingBox();

	void SetPositions(int xtop, int ytop, int xleft, int yleft, int xright, int yright, int xbot, int ybot); //Sets the boudning box dimensions
	void Draw(); //Draws the bounding box

private:

	float m_xtop, m_ytop, m_xleft, m_yleft, m_xright, m_yright, m_xbot, m_ybot;


	cD3DManager* m_pD3DMgr;
	cD3DXSpriteMgr* m_pD3DSRMgr;

	cD3DXTexture* verTex;
	cD3DXTexture* horizTex;
};