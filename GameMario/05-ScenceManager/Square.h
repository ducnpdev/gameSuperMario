#pragma once
#include "GameObject.h"
#include "Define.h"

class CSquare :public CGameObject
{
public:
	CSquare();
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

