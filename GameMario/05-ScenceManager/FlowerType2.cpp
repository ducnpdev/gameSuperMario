#include "Flower.h"
#include "Bullet.h"
#include "FlowerType2.h"
#include "PlayScence.h"
CFlowerType2::CFlowerType2(float x, float y)
{
	originX = x; 
	originY = y;
	SetState(FLOWER_STATE_INOPEN_MOUTH);
	time = GetTickCount();
}

void CFlowerType2::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + 16;
	bottom = y + 30;
}

void CFlowerType2::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt,coObjects);
	y += dy;
	
	if (vy < 0 && y < originY - 18) {
		time = GetTickCount();
		SetState(FLOWER_STATE_OPEN_MOUTH);
	}
	if (GetTickCount() - time > TIME_APPEAR1) {
		SetState(FLOWER_STATE_INOPEN_MOUTH);
	}
	if (GetTickCount() - time > TIME_APPEAR) {
		vy = -FLOWER_SPEED;
	}
}

void CFlowerType2::Render()
{
	
	int ani = FLOWER_BLUE_ANI_INOPEN;
	if (state == FLOWER_STATE_OPEN_MOUTH) {
		ani = FLOWER_BLUE_ANI_OPEN;
	}
	if (state == FLOWER_STATE_INOPEN_MOUTH) {
		ani = FLOWER_BLUE_ANI_INOPEN;
	}
	animation_set->at(ani)->Render(x, y);
	// RenderBoundingBox();
}

void CFlowerType2::SetState(int state)
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

// void CFlowerType2::Fire()
// {
// 	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
// 	CGameObject* obj = NULL;
// 	obj = new CBullet();
// 	// General object setup
// 	obj->SetPosition(x, y + BULLET_POSITION_Y);
// 	LPANIMATION_SET ani_set = animation_sets->Get(OBJECT_TYPE_BULLET);
// 	obj->SetAnimationSet(ani_set);
// 	dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene())->AddObject(obj);
// 	//objects.push_back(obj);
// }
