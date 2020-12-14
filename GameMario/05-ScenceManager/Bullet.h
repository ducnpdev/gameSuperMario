#pragma once
#include "GameObject.h"
#include "Define.h"
#include "Utils.h"

class CBullet : public CGameObject
{
    int directionX;
    int directionY;

public:
    CBullet(int dirX, int dirY);
    virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
    virtual void Render();
    virtual void SetState(int state);
};
