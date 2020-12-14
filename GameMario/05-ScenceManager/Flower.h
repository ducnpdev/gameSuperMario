#pragma once
#include "Define.h"
#include "Utils.h"
#include "GameObject.h"
class CFlower : public CGameObject
{
    DWORD time;
    int type;
    float originX;
    float originY;
public:
    CFlower(float x, float y, int type);
    virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    virtual void Render();
    virtual void SetState(int state);
    void Fire(int directionX, int directionY);
    void Moving(int type);
};

