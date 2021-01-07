#include "ItemFly.h"

CItemFly::CItemFly(int t)
{
	time = GetTickCount();
	type = t;
}

void CItemFly::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// 
	CGameObject::Update(dt, coObjects);
	switch (type)
	{
	case 1:
		vy = NORMAL_SPEED;
		vx = NORMAL_SPEED;
		break;
	case 2:
		vy = -NORMAL_SPEED;
		vx = NORMAL_SPEED;
		break;
	case 3:
		vy = NORMAL_SPEED;
		vx = -NORMAL_SPEED;
		break;
	case 4:
		vy = -NORMAL_SPEED;
		vx = -NORMAL_SPEED;
		break;
	default:
		break;
	}
	y += dy;
	x += dx;
	if (GetTickCount() - time > NUMBER_700) {
		SetStateObjectDelete(NUMBER_1);
	}
}

void CItemFly::Render()
{
	int ani = 0;
    animation_set->at(ani)->Render(x, y);
	// RenderBoundingBox();
}

void CItemFly::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
    left = x;
	top = y;
	right = x + NUMBER_10;
	bottom = y + NUMBER_10;
}

void CItemFly::SetState(int state)
{
	CGameObject::SetState(state);
}
