#include "IntroGoomba.h"
CIntroGoomba::CIntroGoomba(float x, float y) {
	origin_x = x;
	origin_y = y;
	initTime = GetTickCount();
	SetState(INTRO_GOOMBA_STATE_IDLE);
}

void CIntroGoomba::Render() {
	 int ani = -1;
	if (state == INTRO_GOOMBA_STATE_IDLE) {
		ani = INTRO_GOOMBA_ANI_IDLE;
	}
	else if (state == INTRO_GOOMBA_STATE_WALK) {
		ani = INTRO_GOOMBA_ANI_WALK;
	}
	else if (state == INTRO_GOOMBA_STATE_DIE) {
		ani = INTRO_GOOMBA_ANI_DIE;
	}
	animation_set->at(ani)->Render(x, y);
	// RenderBoundingBox();
}

void CIntroGoomba::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	CGameObject::Update(dt, coObjects);
	if (GetTickCount() - initTimeDie > 500 && initTimeDie != 0) {
		SetPosition(1000, 1000);
	}

	if (GetTickCount() - initTime > 8200 && state == INTRO_GOOMBA_STATE_IDLE) {
		SetState(INTRO_GOOMBA_STATE_WALK);
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
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CIntroGoomba::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	left = x;
	top = y;
	right = x + 18;
	bottom = y + 16;
	if (state == INTRO_GOOMBA_STATE_DIE) {
		bottom = y + 6;
	}
}

void CIntroGoomba::SetState(int state) {
	CGameObject::SetState(state);
	switch (state) {
	case INTRO_GOOMBA_STATE_IDLE:
		vy = 0.08f;
		vx = 0;
		break;
	case INTRO_GOOMBA_STATE_WALK:
		vy = 0.08f;
		vx = -0.05f;
		break;
	case INTRO_GOOMBA_STATE_DIE:
		vx = 0; 
		vy = 0.08f;
		break;
	default:
		break;
	}
}

void CIntroGoomba::deleteObject(vector<LPGAMEOBJECT>& coObjects, int i) {
	coObjects.erase(coObjects.begin() + i);
}