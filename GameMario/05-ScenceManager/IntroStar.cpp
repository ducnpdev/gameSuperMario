#include "IntroStar.h"
CIntroStar::CIntroStar(float x, float y) {
	origin_x = x;
	origin_y = y;
	initTime = GetTickCount();
	SetState(INTRO_STAR_STATE_INIT);
}

void CIntroStar::Render() {
	int ani = -1;
	animation_set->at(0)->Render(x, y);
}

void CIntroStar::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	CGameObject::Update(dt, coObjects);
	if (state != INTRO_STAR_STATE_FLY) {
		vy = 0.08f;
	}
	if (state != INTRO_STAR_STATE_INIT && y < 90) {
		SetState(INTRO_STAR_STATE_INIT);
	}
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
			if (dynamic_cast<CBrickFloor*>(e->obj)) {
				SetState(INTRO_STAR_STATE_FLY);
			}
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CIntroStar::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	left = x;
	top = y;
	right = x + 17;
	bottom = y + 18;
}

void CIntroStar::SetState(int state) {
	CGameObject::SetState(state);
	switch (state) {
	case INTRO_STAR_STATE_FLY:
		vx = 0.08f;
		vy = -0.08f;
	case INTRO_STAR_STATE_DOWN:

	default:
		break;
	}
}
