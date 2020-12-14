#include "BrickColliBroken.h"

CBrickColliBroken::CBrickColliBroken() {
	// type = OBJECT_TYPE_BRICK;
	// state = BRICK_STATE_ANIMATION;
}
void CBrickColliBroken::Render()
{
	int ani = BRICK_COLLISION_BROKENT_ANI;
	animation_set->at(ani)->Render(x, y);
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
	switch (state) {
	case BRICK_STATE_ANIMATION:
		vx = 0;
		vy = 0;
		break;
	case BRICK_STATE_DIE:
		vx = 0;
		vy = 0;
		break;
	}
}
