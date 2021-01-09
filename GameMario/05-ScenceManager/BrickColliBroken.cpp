#include "BrickColliBroken.h"
#include "PlayScence.h"
#include "Game.h"
CBrickColliBroken::CBrickColliBroken(int t)
{
	type = t;
}
void CBrickColliBroken::Render()
{
	// ani = 0:brick, 
	// ani = 1: gold, 
	// ani = 2: item,
	// ani = 3: concrete, 
	// ani = 4: item after when collision, la chu P sau khi va cham
	// type = 2: la chu P
	int ani = BRICK_BROKEN_ANI_TYPE_BRICK;
	float tmpx = x;
	if (activeGold) ani = BRICK_BROKEN_ANI_TYPE_GOLD;
	if (!activeGold) ani = BRICK_BROKEN_ANI_TYPE_BRICK;
	if (type == 2)
	{
		ani = BRICK_BROKEN_ANI_TYPE_LETTER_P;
		if (state == BRICK_COLLISION_BROKENT_ITEM_AFTER_COLLISON) ani = BRICK_BROKEN_ANI_TYPE_LETTER_P_AFTER_COLLISIOn;
	}
	 
	if (type == 3 && !allowRenderItem) ani = BRICK_BROKEN_ANI_TYPE_BRICK_CONCRETE;
	if(state == BRICK_BROKEN_STATE_CHANGE_GOLD_BRICK) ani = 0;
	animation_set->at(ani)->Render(tmpx, y);
	// RenderBoundingBox();
}
void CBrickColliBroken::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt, coObjects);
	if(GetTickCount() - timeBrickBrokenRelive > 5000 && timeBrickBrokenRelive != 0){
		// if(type==1){
		//	SetState(BRICK_BROKEN_STATE_CHANGE_GOLD_BRICK);
		//	DebugOut(L"111111111111 \n");
		// }
		dynamic_cast<CPlayScene *>(CGame::GetInstance()->GetCurrentScene())->SetChangeBrickCollisionGold(false);
	}
	
}

void CBrickColliBroken::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + BRICK_BBOX_WIDTH;
	b = y + BRICK_BBOX_HEIGHT;
}

void CBrickColliBroken::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BRICK_COLLISION_BROKENT_NOT_COLLISION:
		vx = NUMBER_0;
		vy = NUMBER_0;
		break;
	default:
		break;
	}
}
