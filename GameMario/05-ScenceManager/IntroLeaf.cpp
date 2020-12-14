#include "IntroLeaf.h"
CIntroLeaf::CIntroLeaf(float x, float y) {
	origin_x = x;
	origin_y = y;
	initTime = GetTickCount();
	SetState(INTRO_LEAF_STATE_INIT);
}

void CIntroLeaf::Render() {
	int ani = -1;
	if (state == INTRO_LEAF_STATE_INIT) {
		ani = INTRO_LEAF_ANI_RIGHT;
	}
	if (state == INTRO_LEAF_STATE_DIRECTION_NAGETIVE) {
		ani = INTRO_LEAF_ANI_LEFT;
	}
	animation_set->at(ani)->Render(x, y);
	// RenderBoundingBox();
}

void CIntroLeaf::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	CGameObject::Update(dt, coObjects);
	//vy = 0.05f;
	y += dy;
 	x += dx;

	// DebugOut(L"Leaf %f: \n", x);
	if (x > origin_x + 10) {
		SetState(INTRO_LEAF_STATE_DIRECTION_NAGETIVE);
	}
	if (x < origin_x - 10) {
		SetState(INTRO_LEAF_STATE_INIT);
	}
}

void CIntroLeaf::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	left = x;
	top = y;
	right = x + 15;
	bottom = y + 20;
}

void CIntroLeaf::SetState(int state) {
	CGameObject::SetState(state);
	switch (state) {
	case INTRO_LEAF_STATE_INIT:
		vy = 0.05f;
		vx = 0.05f;
		break;
	case INTRO_LEAF_STATE_DIRECTION_NAGETIVE:
		vy = 0.05f;
		vx = -0.05f;
		break;
		//vx = -0.05f;
		break;
	default:
		break;
	}
}
