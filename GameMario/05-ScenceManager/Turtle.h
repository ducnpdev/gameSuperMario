#pragma once
#include "GameObject.h"
#include "Define.h"
#include "Utils.h"
#include "BrickFloor.h"
#include "Brick.h"
#include "Mario.h"
class CTurtle : public CGameObject
{
public: 
	int turtle_nx;
	int turtleTypeRender;

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
};

