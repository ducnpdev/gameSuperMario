#pragma once
#include "GameObject.h"
#include "Define.h"
#include "Utils.h"

class CFlowSwitchScene : public CGameObject
{
public:
    CFlowSwitchScene();
    virtual void Render();
    virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
    virtual void SetState(int state);
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

};

