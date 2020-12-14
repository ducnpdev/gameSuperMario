#include "Flower.h"
#include "Bullet.h"
#include "PlayScence.h"
CFlower::CFlower(float x, float y, int t)
{
	type = t;
	originX = x; 
	originY = y;
	SetState(FLOWER_STATE_INOPEN_MOUTH);
	time = GetTickCount();
}

void CFlower::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + 16;
	bottom = y + 30;
}

void CFlower::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CMario* mario = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	CGameObject::Update(dt,coObjects);
	y += dy;
	/*DebugOut(L"typeFlower %d \n", typeFlower);
	if (typeFlower) {
		Moving(typeFlower);
	}*/
	if (vy < 0 && y < originY - FLOWER_POSITION_MOVEMENT) {
		time = GetTickCount();
		SetState(FLOWER_STATE_OPEN_MOUTH);
		if (mario->x < originX){
			if (mario->y > NUMBER_70) {
				// -1: left or above
				Fire(NUMBER_AM_1,NUMBER_1);
			}
			else {
				Fire(NUMBER_AM_1, NUMBER_AM_1);
			}
		}
		else if (mario->x > originX) {
			if (mario->y > 70) {
				Fire(NUMBER_1, NUMBER_1);
			}
			else {
				Fire(NUMBER_1, NUMBER_AM_1);
			}
		}
	}
	if (GetTickCount() - time > TIME_APPEAR1) {
		SetState(FLOWER_STATE_INOPEN_MOUTH);
	}
	if (GetTickCount() - time > TIME_APPEAR) {
		vy = -NUMBER_FLY_SPEED;
	}
}

void CFlower::Render()
{
	CMario* mario = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	int ani = 0;
	if (state == FLOWER_STATE_OPEN_MOUTH) {
		if (mario->x < originX) {
			if (mario->y > NUMBER_70) {
				ani = FLOWER_RED_ANI_OPEN_MOUTH_BELOW_LEFT;
				if (type == NUMBER_2) {
					ani = FLOWER_BLUE_ANI_OPEN_MOUTH_BELOW_LEFT;
				}
			}
			else {
				ani = FLOWER_RED_ANI_OPEN_MOUTH_ABOVE_LEFT;
				if (type == NUMBER_2) {
					ani = FLOWER_BLUE_ANI_OPEN_MOUTH_ABOVE_LEFT;
				}
			}
		}
		else {
			if (mario->y > NUMBER_70) {
				ani =  FLOWER_RED_ANI_OPEN_MOUTH_BELOW_RIGHT;
				if (type == NUMBER_2) {
					ani = FLOWER_BLUE_ANI_OPEN_MOUTH_BELOW_RIGHT;
				}
			}
			else {
				ani = FLOWER_RED_ANI_OPEN_MOUTH_ABOVE_RIGHT;
				if (type == NUMBER_2) {
					ani = FLOWER_BLUE_ANI_OPEN_MOUTH_ABOVE_RIGHT;
				}
			}
		}
	}
	if (state == FLOWER_STATE_INOPEN_MOUTH) {
		if (mario->x < originX) {
			if (mario->y > NUMBER_70) {
				ani = FLOWER_RED_ANI_INOPEN_MOUTH_BELOW_LEFT;
				if (type == NUMBER_2) {
					ani = FLOWER_BLUE_ANI_INOPEN_MOUTH_BELOW_LEFT;
				}
			}
			else {
				ani = FLOWER_RED_ANI_INOPEN_MOUTH_ABOVE_LEFT;
				if (type == NUMBER_2) {
					ani = FLOWER_BLUE_ANI_INOPEN_MOUTH_ABOVE_LEFT;
				}
			}
		}
		else {
			if (mario->y > NUMBER_70) {
				ani = FLOWER_RED_ANI_INOPEN_MOUTH_BELOW_RIGHT;
				if (type == NUMBER_2) {
					ani = FLOWER_BLUE_ANI_INOPEN_MOUTH_BELOW_RIGHT;
				}
			}
			else {
				ani = FLOWER_RED_ANI_INOPEN_MOUTH_ABOVE_RIGHT;
				if (type == NUMBER_2) {
					ani = FLOWER_BLUE_ANI_INOPEN_MOUTH_ABOVE_RIGHT;
				}
			}
		}
	}
	animation_set->at(ani)->Render(x, y);
	// RenderBoundingBox();
}

void CFlower::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case FLOWER_STATE_INOPEN_MOUTH:
		vy = NUMBER_FLY_SPEED;
		vx = 0;
		break;
	case FLOWER_STATE_OPEN_MOUTH:
		vy = 0;
		vx = 0;
		break;
	case FLOWER_DIE_STATE:
		vy = 0;
		vx = 0;
		break;
	default:
		break;
	}
}

void CFlower::Fire(int directionX, int directionY)
{
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	CGameObject* obj = NULL;
	obj = new CBullet(directionX, directionY);
	obj->SetPosition(x, y + BULLET_POSITION_Y);
	LPANIMATION_SET ani_set = animation_sets->Get(OBJECT_TYPE_BULLET);
	obj->SetAnimationSet(ani_set);
	dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene())->AddObject(obj);
}

void CFlower::Moving(int type)
{
	CMario* mario = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	switch (type)
	{
	case NUMBER_1:
		if (vy < 0 && y < originY - FLOWER_POSITION_MOVEMENT) {
			time = GetTickCount();
			SetState(FLOWER_STATE_OPEN_MOUTH);
			if (mario->x < originX) {
				if (mario->y > NUMBER_70) {
					// -1: left or above
					Fire(NUMBER_AM_1, NUMBER_1);
				}
				else {
					Fire(NUMBER_AM_1, NUMBER_AM_1);
				}
			}
			else if (mario->x > originX) {
				if (mario->y > 70) {
					Fire(NUMBER_1, NUMBER_1);
				}
				else {
					Fire(NUMBER_1, NUMBER_AM_1);
				}
			}
		}
		if (GetTickCount() - time > TIME_APPEAR1) {
			SetState(FLOWER_STATE_INOPEN_MOUTH);
		}
		if (GetTickCount() - time > TIME_APPEAR) {
			vy = -NUMBER_FLY_SPEED;
		}
	case NUMBER_2:
		if (vy < 0 && y < originY - FLOWER_POSITION_MOVEMENT) {
			time = GetTickCount();
			SetState(FLOWER_STATE_OPEN_MOUTH);
			//if (mario->x < originX) {
			//	if (mario->y > NUMBER_70) {
			//		// -1: left or above
			//		Fire(NUMBER_AM_1, NUMBER_1);
			//	}
			//	else {
			//		Fire(NUMBER_AM_1, NUMBER_AM_1);
			//	}
			//}
			//else if (mario->x > originX) {
			//	if (mario->y > 70) {
			//		Fire(NUMBER_1, NUMBER_1);
			//	}
			//	else {
			//		Fire(NUMBER_1, NUMBER_AM_1);
			//	}
			//}
		}
		if (GetTickCount() - time > TIME_APPEAR1) {
			SetState(FLOWER_STATE_INOPEN_MOUTH);
		}
		if (GetTickCount() - time > TIME_APPEAR) {
			vy = -NUMBER_FLY_SPEED;
		}
	default:
		break;
	}
	
}
