#pragma once
#include "GameObject.h"
#include "Define.h"
class CCloud : public CGameObject
{
public:
	CCloud();
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};
