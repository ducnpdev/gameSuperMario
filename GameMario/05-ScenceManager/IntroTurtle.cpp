#include "IntroTurtle.h"
CIntroTurtle::CIntroTurtle(float x, float y) {
	origin_x = x;
	origin_y = y;
	initTime = GetTickCount();
	SetState(INTRO_TURTLE_STATE_IDLE);
}

void CIntroTurtle::Render() {
	int ani = 0;
	if (state == INTRO_TURTLE_STATE_IDLE || state == INTRO_TURTLE_STATE_IDLE_COLIISION_ABOVE_PLAYERSECOND) {
		ani = INTRO_TURTLE_ANI_IDLE;
	}
	else if (state == INTRO_TURTLE_STATE_WALK_RIGHT) {
		ani = INTRO_TURTLE_ANI_WALK;
	}
	else if (state == INTRO_TURTLE_STATE_OUT_MAP) {
		ani = INTRO_TURTLE_ANI_WALK;
	}
	else if (state == INTRO_TURTLE_STATE_WALK_LEFT) {
		ani = INTRO_TURTLE_ANI_WALK;
	}
	else if (state == INTRO_TURTLE_STATE_WALK_LEFT_FAST || state == INTRO_TURTLE_STATE_WALK_RIGHT_SESSION2) {
		ani = INTRO_TURTLE_ANI_WALK;
	}
	
	animation_set->at(ani)->Render(x, y);
	// RenderBoundingBox();
}

void CIntroTurtle::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	CGameObject::Update(dt, coObjects);
	/*vy = 0.08f;*/
	DebugOut(L"vx, vy: %f %f \n", vx, x);
	DebugOut(L"state: %d \n", state);
	DWORD now = GetTickCount();
	if (now - initTime > 12650) {
		if (state == INTRO_TURTLE_STATE_WALK_RIGHT) {
			SetState(INTRO_TURTLE_STATE_OUT_MAP);
		}
	}
	if (now - initTime > 14000) {
		if (state == INTRO_TURTLE_STATE_OUT_MAP) {
			vy = 0.08f;
			vx = -0.05f;
			//DebugOut(L"2222222222222 \n");
			//SetState(INTRO_TURTLE_STATE_WALK_LEFT);
		}
	}
	if (now - initTime > 16500) {
		if (state == INTRO_TURTLE_STATE_OUT_MAP) {
			SetState(INTRO_TURTLE_STATE_WALK_LEFT_FAST);
		}
	}

	if (now - collisionTimeSession2 > 1000 && collisionTimeSession2 != 0) {
		SetState(INTRO_TURTLE_STATE_WALK_RIGHT_FAST_SESSION2);
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
			if (dynamic_cast<CIntroTurtleBrack*>(e->obj)) {
				
				CIntroTurtleBrack* turtleblack = dynamic_cast<CIntroTurtleBrack*>(e->obj);
				//if (turtleblack->GetState() == INTRO_PLAYER_SECOND_STATE_LEVEL3_WALK_RIGHT) {
				turtleblack->SetState(INTRO_TURTLE_BLACK_STATE_FLY);
				turtleblack->SetInitTimeDie(GetTickCount());
				SetState(INTRO_TURTLE_STATE_WALK_RIGHT);

				//}
				// DebugOut(L"Turtle collision with  TurtleBrack\n");
			}
			if (dynamic_cast<CIntroPlayerSecond*>(e->obj)) {
				if (e->ny < 0) {
					DebugOut(L"Turtle collision with  CIntroPlayerSecond\n");
				}
			}
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CIntroTurtle::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	left = x;
	top = y;
	right = x + 17;
	bottom = y + 17;
	/*if (state == INTRO_TURTLE_STATE_WALK_LEFT) {
		bottom = y + 17;
	}
	if (state == INTRO_TURTLE_STATE_WALK_RIGHT_SESSION2) {
		bottom = y + 20;
	}*/
}

void CIntroTurtle::SetState(int state) {
	CGameObject::SetState(state);
	switch (state) {
	case INTRO_TURTLE_STATE_IDLE_COLIISION_ABOVE_PLAYERSECOND:
		vy = 0.0f;
		vx = 0.0f;
		break;
	case INTRO_TURTLE_STATE_IDLE:
		vy = 0.08f;
		vx = 0;
		break;
	case INTRO_TURTLE_STATE_WALK_RIGHT:
		vy = 0.08f;
		vx = 0.2f;
		break;
	case INTRO_TURTLE_STATE_OUT_MAP:
		vy = 0.08f;
		vx = 0.0f;
		break;
	case INTRO_TURTLE_STATE_WALK_LEFT:
		vy = 0.08f;
		vx = -0.05f;
		break;
	case INTRO_TURTLE_STATE_WALK_LEFT_FAST:
		vy = 0.08f;
		vx = -0.072f;
		break;
	case INTRO_TURTLE_STATE_WALK_RIGHT_SESSION2:
		vy = 0.05f;
		vx = 0.05f;
		break;
	case INTRO_TURTLE_STATE_WALK_RIGHT_FAST_SESSION2:
		vy = 0.05f;
		vx = 0.1f;
	default:
		break;
	}
}
