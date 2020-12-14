#include "IntroBackgroundSuper.h"
CIntroBackgroundSuper::CIntroBackgroundSuper(int t, int p) {
	type = t;
	breakPosY = p;
	initTime = GetTickCount();
	SetState(INTRO_BACKGROUND_SUPER_STATE_INIT);
}

void CIntroBackgroundSuper::Render() {
	int ani = 0;
    if (state ==  INTRO_BACKGROUND_SUPER_STATE_INIT){
		ani = INTRO_BACKGROUND_SUPER_ANI_INIT;
    }
	animation_set->at(ani)->Render(x, y);
	//RenderBoundingBox();
}

void CIntroBackgroundSuper::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	CGameObject::Update(dt, coObjects);
	y += dy;
	if (type == 1 && y > breakPosY) {
		vy = 0;
	}
	if (type == 2 && y > breakPosY) {
		vy = 0;
	}
	if (type == 3 && y > breakPosY) {
		vy = 0;
	}
	if (type == 4 && y > breakPosY) {
		vy = 0;
	}
	
}

void CIntroBackgroundSuper::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	left = x;
	top = y;
	right = x + 30;
	bottom = y + 50;
}

void CIntroBackgroundSuper::SetState(int state) {
	CGameObject::SetState(state);
	switch (state) {
	case INTRO_BACKGROUND_SUPER_STATE_INIT:
        vx = 0.0f;
        vy = 0.08f;
		break;
	default:
		break;
	}
}
