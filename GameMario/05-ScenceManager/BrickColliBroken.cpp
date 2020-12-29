#include "BrickColliBroken.h"

CBrickColliBroken::CBrickColliBroken(int t)
{
	type = t;
}
void CBrickColliBroken::Render()
{
	// ani = 0:brick, 
	// ani = 1: gold, 
	// ani = 2: item,
	// ani = 3: concrete, 
	// ani = 4: item after when collision 
	int ani = BRICK_COLLISION_BROKENT_ANI;
	float tmpx = x;
	if (activeGold) ani = 1;
	if (type == 2)
	{
		ani = 2;
		if (state == BRICK_COLLISION_BROKENT_ITEM_AFTER_COLLISON) ani = 4;
	}
	if (type == 3 && !allowRenderItem) ani = 3;
	animation_set->at(ani)->Render(tmpx, y);
	// RenderBoundingBox();
}
void CBrickColliBroken::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt, coObjects);
}

void CBrickColliBroken::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + BRICK_BBOX_WIDTH;
	b = y + BRICK_BBOX_HEIGHT;
}

void CBrickColliBroken::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BRICK_COLLISION_BROKENT_NOT_COLLISION:
		vx = NUMBER_0;
		vy = NUMBER_0;
		break;
	default:
		break;
	}
}
