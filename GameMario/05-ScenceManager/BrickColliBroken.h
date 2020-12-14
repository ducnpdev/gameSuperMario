#pragma once
#include "GameObject.h"
#include "Define.h"
#include "Utils.h"

class CBrickColliBroken : public CGameObject
{
    //	int typeItemRender;
public:
	CBrickColliBroken();
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void SetState(int state);
	// void SetTypeItemRender(int typeItemRender);
	// int GetTypeItemRender();
};

