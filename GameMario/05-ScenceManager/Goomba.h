#pragma once
#include "GameObject.h"
#include "Define.h"
#include "Utils.h"
#include "BrickFloor.h"
#include "Money.h"
#include "PlayScence.h"
#include "Scence.h"

class CGoomba : public CGameObject
{
	bool deleteGoombaObj = false;
	DWORD timeDie;
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
};