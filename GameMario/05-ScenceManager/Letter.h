#pragma once
#include "GameObject.h"
#include "Define.h"
#include "Utils.h"
class CLetter : public CGameObject
{
public:
	CLetter();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void SetState(int state);
};

