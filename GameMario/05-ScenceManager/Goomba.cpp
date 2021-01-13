#include "Goomba.h"
CGoomba::CGoomba()
{
	type = OBJECT_TYPE_GOOMBA;
	SetState(GOOMBA_STATE_WALKING);
	listMarioColiding.push_back(OBJECT_TYPE_GOOMBA);
}

void CGoomba::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + GOOMBA_BBOX_WIDTH;
	if (state == GOOMBA_STATE_DIE)
		bottom = y + GOOMBA_BBOX_HEIGHT_DIE;
	else
		bottom = y + GOOMBA_BBOX_HEIGHT;
}

void CGoomba::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt, coObjects);
	vy = 0.009f * dt;
	DWORD now = GetTickCount();
	if (now - timeDie > TIME_DIE && timeDie != NUMBER_0)
	{
		RenderMoney(NUMBER_100, x, y);
		SetStateObjectDelete(NUMBER_1);
		CHud::GetInstance()->AddNumberMoney(NUMBER_100);
	}

	if (now - timeChangeDirection < 300 && timeChangeDirection != NUMBER_0)
	{
		vy = -0.1f;
	}
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();
	float min_tx, min_ty, nx = 0, ny;
	float rdx = 0;
	float rdy = 0;
	if (state != GOOMBA_STATE_START_DIE_COLLISION_TURTLR)
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
		if (nx != 0)
			vx = 0;
		if (ny != 0)
			vy = 0;
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CBrickFloor *>(e->obj))
			{
				if (e->nx < 0)
					vx = -GOOMBA_WALKING_SPEED;
				if (e->nx > 0)
					vx = GOOMBA_WALKING_SPEED;
			}
			if (dynamic_cast<CTurtle *>(e->obj))
			{
				SetState(GOOMBA_STATE_START_DIE_COLLISION_TURTLR);
				timeChangeDirection = GetTickCount();
			}
			if (dynamic_cast<CBrick *>(e->obj))
			{
				if (e->nx < 0)
				{
					vx = -GOOMBA_WALKING_SPEED;
				}
				if (e->nx > 0)
				{
					vx = GOOMBA_WALKING_SPEED;
				}
			}
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CGoomba::Render()
{
	int ani = GOOMBA_ANI_WALKING;
	if (state == GOOMBA_STATE_DIE)
		ani = GOOMBA_ANI_DIE;
	if (state == GOOMBA_STATE_START_DIE_COLLISION_TURTLR)
		ani = GOOMBA_ANI_DIE_COLLISION_TURTLR;
	animation_set->at(ani)->Render(x, y);
	// RenderBoundingBox();
}

void CGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case GOOMBA_STATE_DIE:
		vx = 0;
		vy = GOOMBA_WALKING_SPEED;
		break;
	case GOOMBA_STATE_WALKING:
		vx = -GOOMBA_WALKING_SPEED;
		vy = GOOMBA_WALKING_SPEED;
		break;
	case GOOMBA_STATE_START_DIE_COLLISION_TURTLR:
		vx = GOOMBA_WALKING_SPEED;
		if(!directionCollition) vx = -GOOMBA_WALKING_SPEED;
		vy = -GOOMBA_DIE_SPEED;
		break;
	}
}

void CGoomba::SetStateDie(int stateDie)
{
	CGameObject::SetStateDie(stateDie);
}

void CGoomba::deleteObject(vector<LPGAMEOBJECT> &coObjects, int i)
{
	coObjects.erase(coObjects.begin() + i);
}

void CGoomba::RenderMoney(int number, float x, float y)
{
	CAnimationSets *animation_sets = CAnimationSets::GetInstance();
	CGameObject *obj = NULL;
	switch (number)
	{
	default:
		obj = new CNumber(0,x, y);
		obj->SetPosition(x, y);
		LPANIMATION_SET ani_set = animation_sets->Get(OBJECT_TYPE_NUMBER);
		obj->SetAnimationSet(ani_set);
		dynamic_cast<CPlayScene *>(CGame::GetInstance()->GetCurrentScene())->AddObject(obj);
		break;
	}
}
