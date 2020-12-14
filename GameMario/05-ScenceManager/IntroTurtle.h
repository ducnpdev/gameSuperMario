#pragma once
#include "GameObject.h"
#include "Define.h"
#include "Utils.h"
#include "BrickFloor.h"
#include "IntroPlayerSecond.h"
#include "IntroTurtleBrack.h"

class CIntroTurtle : public CGameObject
{
    float origin_x;
	float origin_y;
	DWORD initTime;
	DWORD collisionTimeSession2;
public:
	CIntroTurtle(float x, float y);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void SetState(int state);
	void SetCollisionTimeSession2(DWORD time) { this->collisionTimeSession2 = time; };
	DWORD GetCollisionTimeSession2(DWORD time) { return this->collisionTimeSession2; };
};

