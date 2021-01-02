#pragma once
#include "GameObject.h"
#include "Define.h"
#include "Utils.h"
#include "BrickFloor.h"
#include "Money.h"
#include "PlayScence.h"
#include "Scence.h"
#include "Turtle.h"
#include "Brick.h"

class CGoomba : public CGameObject
{
	bool deleteGoombaObj = false;
	DWORD timeDie;
	DWORD timeChangeDirection;
	bool directionCollition = true; // true collision right, false collision left

public: 	
	CGoomba();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	
	virtual void SetState(int state);
	//
	virtual void SetStateDie(int stateDie);
	
	virtual void deleteObject(vector<LPGAMEOBJECT> &coObjects, int i);
	void SetTimeStartDie(DWORD time) { this->timeDie = time; }
	DWORD GetTimeStartDie() { return this->timeDie; }
	void RenderMoney(int number, float x, float y);

	void SetTimeChangeDirection(DWORD time) { this->timeChangeDirection = time; }
	DWORD GetTimeChangeDirection() { return this->timeChangeDirection; }
	
	void SetDirectionCollition(bool _b = true) { this->directionCollition = _b; }
	bool GetDirectionCollition() { return this->directionCollition; }
};