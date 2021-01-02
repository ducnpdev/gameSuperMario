#pragma once
#include "GameObject.h"
#include "Define.h"
#include "Utils.h"
#include "BrickFloor.h"
#include "Brick.h"
#include "Mario.h"
#include "BrickColliBroken.h"

class CTurtle : public CGameObject
{
public: 
	int turtle_nx;
	int turtleTypeRender;
	DWORD timeChangeDirection;
	bool directionCollition = true; // true collision right, false collision left

public:
	CTurtle(int type);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void SetState(int state);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void SetTurtle_nx(int turtule_nx) { this->turtle_nx = turtle_nx; };
	int GetTurtle_nx() { return this->turtle_nx; };

	void SetTypeItemRender(int type) { this->turtleTypeRender = type; };
	int GetTypeItemRender() { return this->turtleTypeRender; }

	void SetTimeChangeDirection(DWORD time) { this->timeChangeDirection = time; }
	DWORD GetTimeChangeDirection() { return this->timeChangeDirection; }
	
	void SetDirectionCollition(bool _b = true) { this->directionCollition = _b; }
	bool GetDirectionCollition() { return this->directionCollition; }

};

