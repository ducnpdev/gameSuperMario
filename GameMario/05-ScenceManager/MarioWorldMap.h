#pragma once
#include <algorithm>
#include <assert.h>
#include "GameObject.h"
#include "Define.h"
#include "Utils.h"
#include "Portal.h"
#include "Game.h"
#include "BrickFloor.h"

class CMarioWorldMap : public CGameObject
{
    int untouchable;
    int marioWorldMapLevel;
public:
    CMarioWorldMap();
    virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();
    virtual void SetState(int state);
    void isCollidingObject(vector<LPGAMEOBJECT>* coObjects, vector<LPGAMEOBJECT>& colidingObjects);
};

