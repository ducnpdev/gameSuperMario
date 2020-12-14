#pragma once
#include "GameObject.h"
#include "Define.h"
#include "Utils.h"
#include "Mario.h"
#include "Brick.h"
#include "BrickFloor.h"
class CMushroom : public CGameObject
{
	float origin_x;
	float origin_y;
	
public:
	CMushroom();
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void SetState(int state);
};

