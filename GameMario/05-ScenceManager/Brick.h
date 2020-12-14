#pragma once
#include "GameObject.h"
#include "Define.h"

class CBrick : public CGameObject
{
	int typeItemRender;
public:
	CBrick();
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void SetState(int state);
	void SetTypeItemRender(int typeItemRender);
	int GetTypeItemRender();

};