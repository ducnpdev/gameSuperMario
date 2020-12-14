#pragma once
#include "Enemies.h"
#include "Define.h"
#include "Utils.h"
#include "GameObject.h"
#include "ParentFlower.h"
class CFlower : public CEnemies
{
    DWORD time;
    int type;
public:
    CFlower(float x, float y, int type);
    virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    virtual void Render();
    virtual void SetState(int state);
    void Fire(int directionX, int directionY);
    void Moving(int type);
};

