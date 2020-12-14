#pragma once
#include "GameObject.h"
#include "Define.h"
#include "Utils.h"
class CNumber : public CGameObject
{
	float origin_x;
	float origin_y;
	DWORD NUMBER_TIME_START;
public:
	CNumber(float x, float y);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void SetState(int state);
	virtual void SetStateDie(int stateDie);
};

