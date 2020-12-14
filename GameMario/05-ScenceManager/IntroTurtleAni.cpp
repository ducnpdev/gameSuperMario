#include "IntroTurtleAni.h"
CIntroTurtleAni::CIntroTurtleAni(float x, float y, int velocity) {
	origin_x = x;
	origin_y = y;
	tyleVeloccity = velocity;
	initTime = GetTickCount();
	SetState(INTRO_TURTLE_ANIMATION_ANI_WALK);
}

void CIntroTurtleAni::Render() {
	int ani = -1;
	animation_set->at(0)->Render(x, y);
}

void CIntroTurtleAni::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	CGameObject::Update(dt, coObjects);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();
	float min_tx, min_ty, nx = 0, ny;
	float rdx = 0;
	float rdy = 0;
	CalcPotentialCollisions(coObjects, coEvents);
	FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
	if (coEventsResult.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;
		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CIntroTurtleAni::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	left = x;
	top = y;
	right = x + 15;
	bottom = y + 26;
}

void CIntroTurtleAni::SetState(int state) {
	CGameObject::SetState(state);
	switch (state) {
	case INTRO_TURTLE_ANIMATION_ANI_WALK:
		vy = 0.05f;
		vx = 0.05f;
		if (tyleVeloccity == 2) {
			vx = 0.06f;
		}
	default:

		break;
	}
}
