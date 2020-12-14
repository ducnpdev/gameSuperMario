#pragma once
#include "GameObject.h"
#include "Define.h"
#include "Utils.h"
#include "BrickFloor.h"
#include "IntroGoomba.h"
#include "IntroTurtle.h"
#include "IntroLeaf.h"

class CIntroPlayerSecond : public CGameObject
{
    float origin_x;
	float origin_y;
	DWORD initTime;
	DWORD level2To3Time;
	DWORD kickTime;
	DWORD collisionTurleTimeSecond;
	DWORD collisionTurleAboveTurle;
	DWORD session2Time;

public:
	CIntroPlayerSecond(float x, float y);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void SetState(int state);
};