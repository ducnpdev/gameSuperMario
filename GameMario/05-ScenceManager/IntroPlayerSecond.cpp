#include "IntroPlayerSecond.h"


CIntroPlayerSecond::CIntroPlayerSecond(float x, float y) {
	origin_x = x;
	origin_y = y;
	initTime = GetTickCount();
	SetState(INTRO_PLAYER_SECOND_BIG_STATE_LEFT);
}

void CIntroPlayerSecond::Render() {
	int ani = -1;
    
	if (state == INTRO_PLAYER_SECOND_BIG_STATE_LEFT) {
		ani = INTRO_PLAYER_SECOND_BIG_ANI_IDLE_LEFT;
	}
	else if (state == INTRO_PLAYER_SECOND_BIG_STATE_IDLE_WALKING_LEFT) {
		ani = INTRO_PLAYER_SECOND_BIG_ANI_WALKING_LEFT;
	}
	else if (state == INTRO_PLAYER_SECOND_BIG_STATE_WALKING_LEFT) {
		ani = INTRO_PLAYER_SECOND_BIG_ANI_WALKING_LEFT;
	}
	else if (state == INTRO_PLAYER_SECOND_BIG_STATE_SITDOWN_LEFT) {
		ani = INTRO_PLAYER_SECOND_BIG_ANI_SITDOWN_LEFT;
	}
	else if (state == INTRO_PLAYER_SECOND_BIG_STATE_JUMP_COLLISION_WITH_LEAF) {
		ani = INTRO_PLAYER_SECOND_LEVEL2_ANI_JUMP_LEFT;
	}
	else if (state == INTRO_PLAYER_SECOND_LEVEL3_STATE_JUMP_WAG_TAIL) {
		ani = INTRO_PLAYER_SECOND_LEVEL3_ANI_WAG_LEFT;
	}
	else if (state == INTRO_PLAYER_SECOND_STATE_LEVEL2_TO_LEVEL3) {
		ani = INTRO_PLAYER_SECOND_ANI_LEVEL2_LEVEL3;
	}
	else if (state == INTRO_PLAYER_SECOND_STATE_LEVEL3_WALK_RIGHT || state == INTRO_PLAYER_SECOND_STATE_LEVEL3_WALKING_RIGHT_SESSION2) {
		ani = INTRO_PLAYER_SECOND_LEVEL3_ANI_WALK_RIGHT;
	}
	else if (state == INTRO_PLAYER_SECOND_STATE_LEVEL3_WALK_LEFT) {
		ani = INTRO_PLAYER_SECOND_LEVEL3_ANI_WALK_LEFT;
	}

	

	else if (state == INTRO_PLAYER_SECOND_STATE_LEVEL3_KICK_RIGHT) {
		ani = INTRO_PLAYER_SECOND_LEVEL3_ANI_KICK_RIGHT;
	}
	else if (state == INTRO_PLAYER_SECOND_STATE_LEVEL3_IDLE_RIGHT) {
		ani = INTRO_PLAYER_SECOND_LEVEL3_ANI_IDLE_RIGHT;
	}
	else if (state == INTRO_PLAYER_SECOND_STATE_LEVEL3_JUMP_COLLISION_TURTLE || state == INTRO_PLAYER_SECOND_STATE_LEVEL3_JUMP_TIME_2_COLLISION_TURTLE) {
		// can doi ani khi va cham vs rua
		ani = INTRO_PLAYER_SECOND_LEVEL2_ANI_JUMP_LEFT;
	}
	else if (state == INTRO_PLAYER_SECOND_STATE_LEVEL3_DOWN_COLLISION_TURTLE) {
		// can doi ani khi va cham vs rua
		ani = INTRO_PLAYER_SECOND_LEVEL3_ANI_IDLE_LEFT;
	}
	else if (state == INTRO_PLAYER_SECOND_STATE_LEVEL3_DOWN_TIME_2_COLLISION_TURTLE || state == INTRO_PLAYER_SECOND_STATE_LEVEL3_IDLE_RIGHT_SESSION2) {
		// can doi ani khi va cham vs rua
		ani = INTRO_PLAYER_SECOND_LEVEL3_ANI_IDLE_RIGHT;
	}
	
	animation_set->at(ani)->Render(x, y);
	// RenderBoundingBox();

}

void CIntroPlayerSecond::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	CGameObject::Update(dt, coObjects);
	//DebugOut(L"PlayerSecond vx, vy: %f %f \n", vx, vy);
	DWORD now = GetTickCount();
	if (now - initTime > 500) {
		if (state == INTRO_PLAYER_SECOND_BIG_STATE_LEFT) {
			SetState(INTRO_PLAYER_SECOND_BIG_STATE_IDLE_WALKING_LEFT);
		}
	}
	if (now - initTime > 1000) {
		if (state == INTRO_PLAYER_SECOND_BIG_STATE_IDLE_WALKING_LEFT) {
			SetState(INTRO_PLAYER_SECOND_BIG_STATE_WALKING_LEFT);
		}
	}
	if (now - initTime > 3500) {
		if (state == INTRO_PLAYER_SECOND_BIG_STATE_WALKING_LEFT) {
			SetState(INTRO_PLAYER_SECOND_BIG_STATE_LEFT);
		}
	}
	if (now - initTime > 4500) {
		if (state == INTRO_PLAYER_SECOND_BIG_STATE_LEFT) {
			SetState(INTRO_PLAYER_SECOND_BIG_STATE_SITDOWN_LEFT);
		}
	}
	if (now - initTime > 5000) {
		if (state == INTRO_PLAYER_SECOND_BIG_STATE_SITDOWN_LEFT) {
			SetState(INTRO_PLAYER_SECOND_BIG_STATE_LEFT);
		}
	}

	if (now - initTime > 6500) {
		if (state == INTRO_PLAYER_SECOND_BIG_STATE_LEFT) {
			SetState(INTRO_PLAYER_SECOND_BIG_STATE_JUMP_COLLISION_WITH_LEAF);
		}
	}
	if (state == INTRO_PLAYER_SECOND_STATE_LEVEL2_TO_LEVEL3 && now - level2To3Time > 200) {
		SetState(INTRO_PLAYER_SECOND_LEVEL3_STATE_JUMP_WAG_TAIL);
	}
	if (state == INTRO_PLAYER_SECOND_STATE_LEVEL3_KICK_RIGHT && now - kickTime > 100) {
		SetState(INTRO_PLAYER_SECOND_STATE_LEVEL3_WALK_RIGHT);
	}
	if (state == INTRO_PLAYER_SECOND_STATE_LEVEL3_WALK_RIGHT && now - kickTime > 1350 && kickTime != 0) {
		SetState(INTRO_PLAYER_SECOND_STATE_LEVEL3_IDLE_RIGHT);
	}
	if (state == INTRO_PLAYER_SECOND_STATE_LEVEL3_IDLE_RIGHT && now - kickTime > 4000) {
		SetState(INTRO_PLAYER_SECOND_STATE_LEVEL3_WALK_LEFT);
	}
	if (state == INTRO_PLAYER_SECOND_STATE_LEVEL3_WALK_LEFT && now - kickTime > 5800) {
		collisionTurleTimeSecond = GetTickCount();
		SetState(INTRO_PLAYER_SECOND_STATE_LEVEL3_JUMP_COLLISION_TURTLE);
	}
	if (state == INTRO_PLAYER_SECOND_STATE_LEVEL3_JUMP_COLLISION_TURTLE && now - collisionTurleTimeSecond > 700) {
		SetState(INTRO_PLAYER_SECOND_STATE_LEVEL3_DOWN_COLLISION_TURTLE);
	}

	if (state == INTRO_PLAYER_SECOND_STATE_LEVEL3_DOWN_COLLISION_TURTLE && now - collisionTurleAboveTurle > 200) {
		SetState(INTRO_PLAYER_SECOND_STATE_LEVEL3_DOWN_TIME_2_COLLISION_TURTLE);
	}

	if (now - session2Time > 500 && session2Time != 0) {
		SetState(INTRO_PLAYER_SECOND_STATE_LEVEL3_WALKING_RIGHT_SESSION2);
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
		// if (ny != 0) vy = 0;
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CIntroTurtle*>(e->obj)) {
				// DebugOut(L"1111111111111: %d \n", state);
				CIntroTurtle* turtle = dynamic_cast<CIntroTurtle*>(e->obj);
				if (state == INTRO_PLAYER_SECOND_STATE_LEVEL3_WALK_RIGHT) {
					if (e->nx < 0) {
						turtle->SetState(INTRO_TURTLE_STATE_WALK_RIGHT);
						SetState(INTRO_PLAYER_SECOND_STATE_LEVEL3_KICK_RIGHT);
						kickTime = GetTickCount();
					}
				}

				if (state == INTRO_PLAYER_SECOND_STATE_LEVEL3_DOWN_COLLISION_TURTLE) {
					turtle->SetState(INTRO_TURTLE_STATE_IDLE);
					//turtle->SetPosition();
					collisionTurleAboveTurle = GetTickCount();
					SetState(INTRO_PLAYER_SECOND_STATE_LEVEL3_JUMP_TIME_2_COLLISION_TURTLE);
				}
				if (state == INTRO_PLAYER_SECOND_STATE_LEVEL3_WALKING_RIGHT_SESSION2) {
					turtle->SetCollisionTimeSession2(GetTickCount());
					 turtle->SetState(INTRO_TURTLE_STATE_WALK_RIGHT_SESSION2);
				}
			}
			if (dynamic_cast<CIntroGoomba*>(e->obj)) {
				CIntroGoomba* goomba = dynamic_cast<CIntroGoomba*>(e->obj);
				goomba->SetState(INTRO_GOOMBA_STATE_DIE);
				goomba->SetInitTimeDie(GetTickCount());
			}
			if (dynamic_cast<CBrickFloor*>(e->obj)) {
				if (state == INTRO_PLAYER_SECOND_LEVEL3_STATE_JUMP_WAG_TAIL) {
					SetState(INTRO_PLAYER_SECOND_STATE_LEVEL3_WALK_RIGHT);
				}
				if (state == INTRO_PLAYER_SECOND_STATE_LEVEL3_DOWN_TIME_2_COLLISION_TURTLE) {
					session2Time = GetTickCount();
					SetState(INTRO_PLAYER_SECOND_STATE_LEVEL3_IDLE_RIGHT_SESSION2);
				}
			}
			if (dynamic_cast<CIntroLeaf*>(e->obj)) {
				CIntroLeaf* leaf = dynamic_cast<CIntroLeaf*>(e->obj);
				level2To3Time = GetTickCount();
				SetState(INTRO_PLAYER_SECOND_STATE_LEVEL2_TO_LEVEL3);
				leaf->SetStateObjectDelete(1);
			}
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	
}

void CIntroPlayerSecond::SetState(int state) {
	CGameObject::SetState(state);
    switch (state) {
	case INTRO_PLAYER_SECOND_BIG_STATE_LEFT: 
		vy = 0.08f;
		vx = 0;
		break;
	case INTRO_PLAYER_SECOND_BIG_STATE_IDLE_WALKING_LEFT:
		vx = 0;
		break;
	case INTRO_PLAYER_SECOND_BIG_STATE_WALKING_LEFT:
		vy = 0.08f;
		vx = -0.05f;
		break;
	case INTRO_PLAYER_SECOND_BIG_STATE_SITDOWN_LEFT:
		vy = 0.08f;
		vx = 0;
		break;
	case INTRO_PLAYER_SECOND_BIG_STATE_JUMP_COLLISION_WITH_LEAF:
		vy = -0.1f;
		vx = 0;
		break;
	case INTRO_PLAYER_SECOND_STATE_LEVEL2_TO_LEVEL3:
		vx = 0;
		vy = 0;
		break;
	case INTRO_PLAYER_SECOND_LEVEL3_STATE_JUMP_WAG_TAIL:
		vy = 0.025f;
		vx = -0.05f;
		break;
	case INTRO_PLAYER_SECOND_STATE_LEVEL3_WALK_RIGHT:
		vy = 0.05f;
		vx = 0.05f;
		break;
	case INTRO_PLAYER_SECOND_STATE_LEVEL3_WALK_LEFT:
		vy = 0.05f;
		vx = -0.05f;
		break;
	case INTRO_PLAYER_SECOND_STATE_LEVEL3_IDLE_RIGHT:
		vy = 0.05f;
		vx = -0.0f;
		break;
	case INTRO_PLAYER_SECOND_STATE_LEVEL3_KICK_RIGHT:
		vy = 0.05f;
		vx = 0.05f;
		break;
	case INTRO_PLAYER_SECOND_STATE_LEVEL3_JUMP_COLLISION_TURTLE:
		vy = -0.05f;
		vx = -0.05f;
		break;
	case INTRO_PLAYER_SECOND_STATE_LEVEL3_JUMP_TIME_2_COLLISION_TURTLE:
		vy = -0.05f;
		vx = -0.02f;
		break;
	case INTRO_PLAYER_SECOND_STATE_LEVEL3_DOWN_COLLISION_TURTLE:
		vy = 0.05f;
		vx = -0.05f;
		break;
	case INTRO_PLAYER_SECOND_STATE_LEVEL3_DOWN_TIME_2_COLLISION_TURTLE:
		vy = 0.05f;
		vx = -0.08f;
		break;
	case INTRO_PLAYER_SECOND_STATE_LEVEL3_IDLE_RIGHT_SESSION2:
		vy = 0.05f;
		vx = 0.0f;
		break;
	case INTRO_PLAYER_SECOND_STATE_LEVEL3_WALKING_RIGHT_SESSION2:
		vy = 0.05f;
		vx = 0.05f;
		break;
	case INTRO_PLAYER_SECOND_STATE_LEVEL3_WALKING_LEFT_SESSION2:

	default:
		break;
	}
}

void CIntroPlayerSecond::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	left = x;
	top = y;
	right = x + 15;
	bottom = y + 26;
}