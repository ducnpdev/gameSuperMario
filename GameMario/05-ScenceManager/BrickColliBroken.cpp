#include "BrickColliBroken.h"

CBrickColliBroken::CBrickColliBroken(int t) {
	type = t;
	// state = BRICK_COLLISION_BROKENT_STATE_INIT;
}
void CBrickColliBroken::Render()
{
	int ani = BRICK_COLLISION_BROKENT_ANI;
	/*if (type  == 1) ani = BRICK_COLLISION_BROKENT_ANI;
	if (type == 2) ani = BRICK_COLLISION_BROKENT_ANI_CHANGE_GOLD;*/
	float tmpx = x;
	if (activeGold) {
		ani = BRICK_COLLISION_BROKENT_ANI_CHANGE_GOLD;
		tmpx += NUMBER_5;
	}
	if (type == NUMBER_3) {
		ani = 2;
	}
	animation_set->at(ani)->Render(tmpx, y);
	// RenderBoundingBox();
}

void CBrickColliBroken::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + BRICK_BBOX_WIDTH;
	b = y + BRICK_BBOX_HEIGHT;

}

void CBrickColliBroken::SetState(int state) {
	CGameObject::SetState(state);
}
