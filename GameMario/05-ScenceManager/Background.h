#pragma once
#include "GameObject.h"
#include "Define.h"
#include "Utils.h"
#include "Portal.h"

class CBackground : public CGameObject
{
	vector<LPSPRITE> sprites;
	vector<vector<int>> position;
	//int level;
public:
	//void load()
	CBackground(vector<LPSPRITE> sprites, vector<vector<int>> position)
	{
		this->sprites = sprites;
		this->position = position;
	}
	virtual void Render(); //them x y trong render 
	 void GetBoundingBox(float& l, float& t, float& r, float& b);
};