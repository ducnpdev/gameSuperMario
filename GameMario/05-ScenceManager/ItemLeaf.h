#pragma once
#include "GameObject.h"
#include "Define.h"
#include "Utils.h"

class CItemLeaf : public CGameObject
{
    float origin_x;
    float origin_y;
    DWORD LEAF_TIME_START;
    DWORD LEAF_TIME_START_X;
public:
    CItemLeaf(float x, float y);
    virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
    virtual void Render();
    virtual void SetState(int state);
    virtual void SetStateDie(int stateDie);
    void SetLeafPosition(float x, float y);
    void isColidingObject(vector<LPGAMEOBJECT> *coObjects, vector<LPGAMEOBJECT> &colidingObjects);
};
