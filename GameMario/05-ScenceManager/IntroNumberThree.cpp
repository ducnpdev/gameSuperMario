#include "IntroNumberThree.h"
CIntroNumberThree::CIntroNumberThree(float x, float y) {
	origin_x = x;
	origin_y = y;
	initTime = GetTickCount();
	SetState(INTRO_PLAYER_BIG_STATE_RIGHT);
}

void CIntroNumberThree::Render() {
	int ani = -1;
	animation_set->at(0)->Render(x, y);
	//RenderBoundingBox();
}

void CIntroNumberThree::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	CGameObject::Update(dt, coObjects);
	vy = 0.08f;
	y += dy;
	if (y > 88) {
		vy = 0;
	}
}

void CIntroNumberThree::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	left = x;
	top = y;
	right = x + 30;
	bottom = y + 50;
}

void CIntroNumberThree::SetState(int state) {
	CGameObject::SetState(state);
	switch (state) {
	case INTRO_PLAYER_BIG_STATE_RIGHT: 
		break;
	default:
		break;
	}
}
