#pragma once
#include "GameObject.h"
#include "Define.h"
class CBrickFloor : public CGameObject
{
	int widthBox;
	int heightBox;
public:
	CBrickFloor(int width,int height);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};