#pragma once
#include "GameObject.h"
#include "Define.h"
#include "Utils.h"
#include "BrickFloor.h"
#include "IntroPlayerSecond.h"
class CIntroTurtleAni : public CGameObject
{
    float origin_x;
	float origin_y;
	DWORD initTime;
	int tyleVeloccity; // *= 2 thì vận tộc hơn * = 1
public:
	CIntroTurtleAni(float x, float y, int veloccity);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void SetState(int state);
};

