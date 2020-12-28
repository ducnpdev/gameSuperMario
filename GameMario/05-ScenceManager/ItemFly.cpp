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
		vy = 0.05f;
		vx = 0.05f;
		break;
	case 2:
		vy = -0.05f;
		vx = 0.05f;
		break;
	case 3:
		vy = 0.05f;
		vx = -0.05f;
		break;
	case 4:
		vy = -0.05f;
		vx = -0.05f;
		break;
	default:
		break;
	}
	y += dy;
	x += dx;
	if (GetTickCount() - time > NUMBER_1000) {

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
	//switch (state) {
	//case INTRO_LEAF_STATE_INIT:
	//	vy = 0.05f;
	//	vx = 0.05f;
	//	break;
	//case INTRO_LEAF_STATE_DIRECTION_NAGETIVE:
	//	vy = 0.05f;
	//	vx = -0.05f;
	//	break;
	//	//vx = -0.05f;
	//	break;
	//default:
	//	break;
	//}
}
