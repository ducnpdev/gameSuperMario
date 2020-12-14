#include "IntroDoor.h"
CIntroDoor::CIntroDoor(float x, float y) {
	origin_x = x;
	origin_y = y;
	initTime = GetTickCount();
	SetState(INTRO_PLAYER_BIG_STATE_RIGHT);
}

void CIntroDoor::Render() {
	animation_set->at(0)->Render(x, y);
	//RenderBoundingBox();
}

void CIntroDoor::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	CGameObject::Update(dt, coObjects);
	//vy = 0.08f;
	if (GetTickCount() - initTime > 1000) {
		vy = -0.08f;
		y += dy;
	}
}

void CIntroDoor::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	left = x;
	top = y;
	right = x + 17;
	bottom = y + 17;
}

void CIntroDoor::SetState(int state) {
	CGameObject::SetState(state);
	switch (state) {
	default:
		break;
	}
}
