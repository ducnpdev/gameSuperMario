#include "IntroTurtleBrack.h"
CIntroTurtleBrack::CIntroTurtleBrack(float x, float y) {
	origin_x = x;
	origin_y = y;
	initTime = GetTickCount();
	SetState(INTRO_TURTLE_BLACK_STATE_IDLE);
}

void CIntroTurtleBrack::Render() {
	int ani = 0;
	if (state == INTRO_TURTLE_BLACK_STATE_IDLE) {
		ani = INTRO_TURTLE_BLACK_ANI_IDLE;
	}
	else if (state == INTRO_TURTLE_BLACK_STATE_FLY || state == INTRO_TURTLE_BLACK_STATE_DOWN) {
		ani = INTRO_TURTLE_BLACK_ANI_FLY;
	}
	animation_set->at(ani)->Render(x, y);
	// RenderBoundingBox();
}

void CIntroTurtleBrack::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	CGameObject::Update(dt, coObjects);
	/*vy = 0.08f;*/
	if (GetTickCount() - initTimeDown > 700 && initTimeDown != 0) {
		SetState(INTRO_TURTLE_BLACK_STATE_DOWN);
	}
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();
	float min_tx, min_ty, nx = 0, ny;
	float rdx = 0;
	float rdy = 0;
	if (state != INTRO_TURTLE_BLACK_STATE_DOWN) {
		CalcPotentialCollisions(coObjects, coEvents);
	}
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
			//	DebugOut(L"111111111111111111111111 \n");
			}
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CIntroTurtleBrack::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	left = x;
	top = y;
	right = x + 17;
	bottom = y + 17;
}

void CIntroTurtleBrack::SetState(int state) {
	CGameObject::SetState(state);
	switch (state) {
	case INTRO_TURTLE_BLACK_STATE_IDLE:
		vy = 0.08f;
		vx = 0;
		break;
	case INTRO_TURTLE_BLACK_STATE_FLY:
		vy = -0.08f;
		vx = 0.05f;
		break;
	case INTRO_TURTLE_BLACK_STATE_DOWN:
		vy = 0.2f;
		vx = 0.03f;
		break;

	default:
		break;
	}
}
