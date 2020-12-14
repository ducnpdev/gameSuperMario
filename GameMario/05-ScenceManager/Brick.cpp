#include "Brick.h"
CBrick::CBrick() {
	state = BRICK_STATE_ANIMATION;
}
void CBrick::Render()
{
	int ani = BRICK_ANI_ANIMATION;
	if (state == BRICK_STATE_DIE || state == BRICK_STATE_DONE){
		ani = BRICK_ANI_DIE;
	}
	animation_set->at(ani)->Render(x, y);
	// RenderBoundingBox();
}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + BRICK_BBOX_WIDTH;
	b = y + BRICK_BBOX_HEIGHT;
}

void CBrick::SetState(int state) {
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

void CBrick::SetTypeItemRender(int typeItemRender) {
	this->typeItemRender = typeItemRender;
}

int CBrick::GetTypeItemRender() {
	return this->typeItemRender;
}
