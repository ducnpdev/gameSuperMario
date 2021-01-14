#pragma once
#include "GameObject.h"
#include "Define.h"
#include "Utils.h"
class CTurtleJump : public CGameObject
{
	DWORD jump_at;
	DWORD timeIntervalJump;
public:
	CTurtleJump();
	void jump();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void SetState(int state);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	// void SetTurtle_nx(int turtule_nx) { this->turtle_nx = turtle_nx; };
	// int GetTurtle_nx() { return this->turtle_nx; };
};

