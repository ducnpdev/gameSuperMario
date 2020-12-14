#pragma once
#include "GameObject.h"
#include "MorningStar.h"
#include "Brick.h"
#include "Define.h"
#include "Mushroom.h"
#include "Turtle.h"
#include "Square.h"
#include "Goombafly.h"
#include "Tail.h"
#include "Hold.h"
#include "Bullet.h"
#include "Flower.h"
#include "FlowerType2.h"

class CMario : public CGameObject
{
	int level;
	int untouchable;
	DWORD untouchable_start;
	float start_x;			// initial position of Mario at scene
	float start_y; 
	//
	int frame = -1;
	bool checkAttact = false;
	DWORD timeAttact;
	DWORD startUpDownLevel;
	bool fast = false;
	CTail* tail;
	int lastTailSwingDirection = 0;
	LPANIMATION ani;
	DWORD second;
public: 
	bool isJump = false;
	CMario(float x = 0.5f, float y = 0.5f);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();
	void SetState(int state);
	void SetLevel(int l) { level = l; y += 20; }
	int GetLevel() { return this->level; }
	void Reset();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	//
	void StartAttact() { checkAttact = true; timeAttact = GetTickCount(); frame = -1; }
	// handle
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	void StartUpDownLevel();
	void HandleUpDownLevel();
	void SetFast(bool b) { this->fast = b; }
	// collision functions
	void ClearCollisionEvent(vector<LPCOLLISIONEVENT> coEvents);
	void HandleHoldCollision(float ny, float dx, float dy, float old_vy);
	// attackment
	void HandleAttack();
	bool GetStateJump() { return this->isJump; }
	// attack function
	void swingTailAttack();
	// mario collision with enemies and down level 
	void downLevel();
	void upLevel();
	// render item when mario collision with brick
	void renderItemCollisionBrick(int type, float x, float y);
};