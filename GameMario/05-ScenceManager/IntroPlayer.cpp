#include "IntroPlayer.h"

CIntroPlayer::CIntroPlayer(float x, float y) {
	origin_x = x;
	origin_y = y;
	initTime = GetTickCount();
	SetState(INTRO_PLAYER_BIG_STATE_RIGHT);
}

void CIntroPlayer::Render() {
	int ani = -1;
	if (state == INTRO_PLAYER_BIG_STATE_RIGHT) {
		ani = INTRO_PLAYER_BIG_ANI_IDLE_RIGHT;
	}else if(state == INTRO_PLAYER_BIG_STATE_LEFT) {
		ani = INTRO_PLAYER_BIG_ANI_IDLE_LEFT;
	}
	else if (state == INTRO_PLAYER_BIG_STATE_IDLE_WALKING_RIGHT) {
		ani = INTRO_PLAYER_BIG_ANI_WALKING_RIGHT;
	}
	else if (state == INTRO_PLAYER_BIG_STATE_WALKING_RIGHT) {
		ani = INTRO_PLAYER_BIG_ANI_WALKING_RIGHT;
	}
	else if (state == INTRO_PLAYER_BIG_STATE_JUMP_RIGHT ) {
		ani = INTRO_PLAYER_BIG_ANI_JUMP_RIGHT;
	}
	else if (state == INTRO_PLAYER_BIG_STATE_DOWN_RIGHT) {
		ani = INTRO_PLAYER_BIG_ANI_IDLE_RIGHT;
	}
	else if (state == INTRO_PLAYER_BIG_STATE_DOWN_RIGHT_1) {
		ani = INTRO_PLAYER_BIG_ANI_IDLE_RIGHT;
	}
	else if (state == INTRO_PLAYER_BIG_STATE_JUMP_RIGHT_1) {
		ani = INTRO_PLAYER_BIG_ANI_JUMP_RIGHT;
	}
	else if (state == INTRO_PLAYER_BIG_STATE_OUT_MAP) {
		ani = INTRO_PLAYER_BIG_ANI_WALKING_LEFT;
	}
	else if (state == INTRO_PLAYER_BIG_STATE_LEVEL2_WALKING_LEFT) {
		ani = INTRO_PLAYER_BIG_ANI_WALKING_LEFT;
	}
	
	animation_set->at(ani)->Render(x, y);
	// RenderBoundingBox();
}

void CIntroPlayer::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	CGameObject::Update(dt, coObjects);
	DWORD now = GetTickCount();
	if (now - initTime > 500) {
		if (state == INTRO_PLAYER_BIG_STATE_RIGHT) {
			SetState(INTRO_PLAYER_BIG_STATE_IDLE_WALKING_RIGHT);
		}
	}
	if (now - initTime > 1000) {
		if (state == INTRO_PLAYER_BIG_STATE_IDLE_WALKING_RIGHT) {
			SetState(INTRO_PLAYER_BIG_STATE_WALKING_RIGHT);
		}
	}
	if (now - initTime > 2000) {
		if (state == INTRO_PLAYER_BIG_STATE_WALKING_RIGHT) {
			SetState(INTRO_PLAYER_BIG_STATE_JUMP_RIGHT);
		}
	}
	if (now - initTime > 3500) {
		if (state == INTRO_PLAYER_BIG_STATE_JUMP_RIGHT) {
			SetState(INTRO_PLAYER_BIG_STATE_DOWN_RIGHT);
		}
	}
	if (now - initTime > 4500) {
		if (state == INTRO_PLAYER_BIG_STATE_DOWN_RIGHT) {
			SetState(INTRO_PLAYER_BIG_STATE_JUMP_RIGHT_1);
		}
	}
	if (now - initTime > 5800) {
		if (state == INTRO_PLAYER_BIG_STATE_JUMP_RIGHT_1) {
			SetState(INTRO_PLAYER_BIG_STATE_DOWN_RIGHT_1);
		}
	}
	if (now - initTime > 7250) {
		if (state == INTRO_PLAYER_BIG_STATE_DOWN_RIGHT_1) {
			SetState(INTRO_PLAYER_BIG_STATE_WALKING_RIGHT);
		}
	}
	if (now - initTime > 10000) {
		if (state == INTRO_PLAYER_BIG_STATE_WALKING_RIGHT) {
			SetState(INTRO_PLAYER_BIG_STATE_OUT_MAP);
			// SetState(INTRO_PLAYER_BIG_STATE_WALKING_RIGHT);
		}
	}
	if (now - initTime > 13000) {
		if (state == INTRO_PLAYER_BIG_STATE_OUT_MAP) {
			SetState(INTRO_PLAYER_BIG_STATE_LEVEL2_WALKING_LEFT);
			/*vy = 0.05f;
			vx = -0.05f;*/
			// SetState(INTRO_PLAYER_BIG_STATE_WALKING_RIGHT);
		}
	}
	if (state == INTRO_PLAYER_BIG_STATE_LEVEL2_WALKING_LEFT && now - initTime > 16000) {
		SetState(INTRO_PLAYER_BIG_STATE_LEFT);
	}
	// DebugOut(L"PlayerSecond x, y: %f %f\n", x, y);
	
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
		//if (ny != 0) vy = 0;
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if(dynamic_cast<CBrickFloor*>(e->obj)) {
			}
			if (dynamic_cast<CIntroPlayerSecond*>(e->obj)) {
				CIntroPlayerSecond* introPlayerSecondTurtle = dynamic_cast<CIntroPlayerSecond*>(e->obj);
			}
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	
}

void CIntroPlayer::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	left = x;
	top = y;
	right = x + 15;
	bottom = y + 26;
}

void CIntroPlayer::SetState(int state) {
	CGameObject::SetState(state);
	switch (state) {
	case INTRO_PLAYER_BIG_STATE_RIGHT: 
		vy = 0.08f;
		vx = 0;
		break;
	case INTRO_PLAYER_BIG_STATE_IDLE_WALKING_RIGHT:
		vy = 0.08f;
		vx = 0;
		break;
	case INTRO_PLAYER_BIG_STATE_WALKING_RIGHT:
		vy = 0.08f;
		vx = 0.05f;
		break;
	case INTRO_PLAYER_BIG_STATE_JUMP_RIGHT:
		vx = 0.05f;
		vy = -0.05f;
		break;
	case INTRO_PLAYER_BIG_STATE_JUMP_RIGHT_1:
		vx = 0.05f;
		vy = -0.1f;
		break;
	case INTRO_PLAYER_BIG_STATE_DOWN_RIGHT:
		vy = 0.05f;
		vx = 0.03f;
		break;
	case INTRO_PLAYER_BIG_STATE_DOWN_RIGHT_1:
		vy = 0.1f;
		vx = 0.03f;
		break;
	case INTRO_PLAYER_BIG_STATE_OUT_MAP:
		vy = 0.0f;
		vx = 0.0f;
		break;
	case INTRO_PLAYER_BIG_STATE_LEVEL2_WALKING_LEFT:
		vy = 0.05f;
		vx = -0.05f;
		break;
	case INTRO_PLAYER_BIG_STATE_LEFT:
		vy = 0.08f;
		vx = 0;
		break;
	default:
		break;
	}
}
