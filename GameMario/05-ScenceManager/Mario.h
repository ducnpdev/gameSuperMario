#pragma once

#include "GameObject.h"
#include "MorningStar.h"
#include "Brick.h"
#include "BrickColliBroken.h"
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
	DWORD timeAddCountArrow;
	int countArrow;

	bool isActiveFly = false;
	bool isJumpHeight = false;
	DWORD timeSwitchScene;
	bool isActiveSwitchScene = false;
	DWORD timeKick;
	bool isActiveWaiSwingTail = false;
	// variable test

	bool isPower = false;

public: 
	bool isJump = false;
	CMario(float x = 0.5f, float y = 0.5f);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	
	void SetState(int state);
	void SetLevel(int l) { level = l; y += NUMBER_20; }
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
	bool GetFast() { return this->isJump; }

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

	void SplusCountArrow();
	void SubCountArrow();
	int GetCountArrow() { return this->countArrow; }

	void SetIsActiveFly(bool _b = true) { this->isActiveFly = _b; }
	bool GetIsActiveFly() { return this->isActiveFly; }

	void SetIsJumpHeight(bool _b = true) { this->isJumpHeight = _b; }
	bool GetIsJumpHeight() { return this->isJumpHeight; }

	void WalkThrough(float _vx, float _vy);

	// timeOut jump collision with item
	void JumpWhenCollision();
	void HandleArrowHud();
	void HandleMarioFly();
	void HandleMarioSwingTail();
	
	void SetIsActiveSwingTail(bool _b = true) { this->isActiveWaiSwingTail = _b; }
	bool GetIsActiveSwingTail() { return this->isActiveWaiSwingTail; }
	
	// collision handles
	void CollisionWithGoomba(LPCOLLISIONEVENT collisionEven);
	void CollisionWithTurtle(LPCOLLISIONEVENT collisionEven);
	void CollisionWithMushroom(LPCOLLISIONEVENT collisionEven);
	void CollisionWithBrickColliBroken(LPCOLLISIONEVENT collisionEven, bool &isCollision);

	void SetIsPower(bool _b = true) { this->isPower = _b; }
	bool GetIsPower() { return this->isPower; }

	void HandlIsPower();

	// mario renders 
	virtual void Render();
	void RenderMarioLevel4(int &ani); // mario fire
};