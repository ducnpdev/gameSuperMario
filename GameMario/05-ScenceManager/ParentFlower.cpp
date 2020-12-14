#include "ParentFlower.h"
#include "FlowerType2.h"

CParentFlower::CParentFlower(float x, float y)
{
    originX = x; 
	originY = y;
	SetState(FLOWER_STATE_INOPEN_MOUTH);
	time = GetTickCount();
}

void CParentFlower::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
    left = x;
	top = y;
	right = x + 16;
	bottom = y + 30;
}

void CParentFlower::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
    CGameObject::Update(dt,coObjects);
	y += dy;
	
	if (vy < 0 && y < originY - FLOWER_POSITION_MOVEMENT) {
		time = GetTickCount();
		SetState(FLOWER_STATE_OPEN_MOUTH);
	}
	if (GetTickCount() - time > TIME_APPEAR1) {
		SetState(FLOWER_STATE_INOPEN_MOUTH);
	}
	if (GetTickCount() - time > TIME_APPEAR) {
		vy = -NUMBER_FLY_SPEED;
	}
}

void CParentFlower::Render()
{
    int ani = FLOWER_FLY_ANI_1;
	if (state == FLOWER_STATE_OPEN_MOUTH) {
		ani = FLOWER_FLY_ANI_0;
	}
	if (state == FLOWER_DIE_STATE) {
		// DebugOut(L"123123 \n");
		ani = FLOWER_FLY_ANI_DIE;
	}
	animation_set->at(ani)->Render(x, y);
}

void CParentFlower::SetState(int state)
{
    CGameObject::SetState(state);
	switch (state)
	{
	case FLOWER_STATE_INOPEN_MOUTH:
		vy = NUMBER_FLY_SPEED;
		vx = 0;
		
		break;
	case FLOWER_STATE_OPEN_MOUTH:
		vy = 0;
		vx = 0;
		break;
	case FLOWER_DIE_STATE:
		vy = 0;
		vx = 0;
		break;
	default:
		break;
	}
}
