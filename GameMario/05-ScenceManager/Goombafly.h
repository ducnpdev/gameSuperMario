#pragma once
#include "GameObject.h"
#include "Utils.h"
#include "Define.h"
#include "Turtle.h"

class CGoombafly : public CGameObject
{
	float goomba_fly_origin_x;
	float goomba_fly_origin_y;
	DWORD jump_at;
	int direction = 1;
	int untouchableGoombaFly;
	DWORD untouchableGoombaFly_start;
	DWORD timeChangeDirection;
	bool directionCollition = true; // true collision right, false collision left

public:
	CGoombafly(float x, float y);
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void SetState(int state);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void jump();
	void calculateVx();
	void SetUntouchableGoombaFly(int untouchableGoombaFly);
	int GetUntouchableGoombaFly();
	void StartUntouchableGoombaFly();

	void SetTimeChangeDirection(DWORD time) { this->timeChangeDirection = time; }
	DWORD GetTimeChangeDirection() { return this->timeChangeDirection; }
	void SetDirectionCollition(bool _b = true) { this->directionCollition = _b; }
	bool GetDirectionCollition() { return this->directionCollition; }

};

