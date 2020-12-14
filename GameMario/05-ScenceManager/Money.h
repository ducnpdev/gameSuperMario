#pragma once
#include "GameObject.h"
#include "Define.h"
#include "Utils.h"
class CMoney : public CGameObject
{
    float origin_x;
    float origin_y;
    bool isCheckMove = false;
    DWORD MONEY_TIME_START;
public: 
    CMoney(float x, float y,bool isCheckMove);

    virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    virtual void Render();
    virtual void SetState(int state);
    virtual void SetStateDie(int stateDie);
    void SetMoneyPosition(float x, float y);
    void isColidingObject(vector<LPGAMEOBJECT>* coObjects, vector<LPGAMEOBJECT>& colidingObjects);
};

