#pragma once
#include "GameObject.h"
#include "Define.h"
#include "Utils.h"
#include "Enemies.h"

class CParentFlower : public CEnemies
{
public:
    DWORD time;
    DWORD time1;

public:
    CParentFlower(float x, float y);
    virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    virtual void Render();
    virtual void SetState(int state);
    //void Fire();
};
