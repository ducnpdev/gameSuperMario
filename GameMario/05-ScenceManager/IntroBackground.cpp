#include "IntroBackground.h"
CIntroBackground::CIntroBackground() {
	//origin_x = x;
	//origin_y = y;
	initTime = GetTickCount();
	SetState(INTRO_BACKGROUND_STATE_INIT);
}

void CIntroBackground::Render() {
	int ani = 0;
	if (state == INTRO_BACKGROUND_STATE_INIT) {
		ani = INTRO_BACKGROUND_ANI_INIT;
	}
	animation_set->at(ani)->Render(x, y);
}

void CIntroBackground::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	CGameObject::Update(dt, coObjects);
}

void CIntroBackground::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	left = x;
	top = y;
	right = x + 15;
	bottom = y + 26;
}

void CIntroBackground::SetState(int state) {
	CGameObject::SetState(state);
	switch (state) {
	case INTRO_BACKGROUND_STATE_INIT:
		vy = 0.0f;
		vx = 0.0f;
		break;
	default:
		break;
	}
}
