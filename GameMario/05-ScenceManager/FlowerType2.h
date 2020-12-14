#pragma once
#include "Enemies.h"
#include "Define.h"
#include "Utils.h"
#include "GameObject.h"
#include "ParentFlower.h"
class CFlowerType2 : public CEnemies
{
    DWORD time;
    int typeFlower;
public:
    CFlowerType2(float x, float y);
    virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    virtual void Render();
    virtual void SetState(int state);
    //void Fire();
};

