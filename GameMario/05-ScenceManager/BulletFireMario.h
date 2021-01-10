#pragma once
#include "GameObject.h"
#include "Define.h"
#include "Utils.h"
#include "BrickFloor.h"
#include "Hold.h"
#include "BrickColliBroken.h"


class CBulletFireMario : public CGameObject
{
    DWORD timeChangeDirection;
    int direction;
public:
    CBulletFireMario(int d);
    virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
    virtual void Render();
    virtual void SetState(int state);
	void Collisions(LPCOLLISIONEVENT e);
    void CollisionGoomba(LPCOLLISIONEVENT e);
    void CollisionTurtle(LPCOLLISIONEVENT e);

    void HandleDeteleItem();

};

