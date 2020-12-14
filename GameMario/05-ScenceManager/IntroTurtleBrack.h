#pragma once
#include "GameObject.h"
#include "Define.h"
#include "Utils.h"
#include "BrickFloor.h"
#include "IntroPlayerSecond.h"
class CIntroTurtleBrack : public CGameObject
{
    float origin_x;
	float origin_y;
	DWORD initTime;
	DWORD initTimeDown;
public:
	CIntroTurtleBrack(float x, float y);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void SetState(int state);
	void SetInitTimeDie(DWORD time) { this->initTimeDown = time; };
	DWORD GetInitTimeDie(DWORD time) { return this->initTimeDown; };
};

