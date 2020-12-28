#pragma once
#include "GameObject.h"
#include "Define.h"
#include "Utils.h"
#include "BrickColliBroken.h"
#include "ItemFly.h"


class CTail : public CGameObject
{
    int damageLevel;
    DWORD activeAt;
    bool isActive = false;
public:
    CTail();
    void SetActive(bool _isActive = true);
    virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    virtual void SetState(int state);
    void isCollidingObject(vector<LPGAMEOBJECT>* coObjects, vector<LPGAMEOBJECT>& colidingObjects);
    void RenderItem(float x, float y);

};

