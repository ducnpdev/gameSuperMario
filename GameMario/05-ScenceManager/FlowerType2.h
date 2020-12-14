#pragma once
#include "Define.h"
#include "Utils.h"
#include "GameObject.h"
class CFlowerType2 : public CGameObject
{
    DWORD time;
    int typeFlower;
    float originX;
    float originY;
public:
    CFlowerType2(float x, float y);
    virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    virtual void Render();
    virtual void SetState(int state);
    //void Fire();
};

