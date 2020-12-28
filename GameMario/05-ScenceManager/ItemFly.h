#pragma once
#include "GameObject.h"
#include "Define.h"
#include "Utils.h"
class CItemFly : public CGameObject
{
	DWORD time;
	int type;
public:
	CItemFly(int t);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void SetState(int state);
};

