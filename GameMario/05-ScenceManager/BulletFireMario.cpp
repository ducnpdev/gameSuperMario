#include "BulletFireMario.h"
#include "PlayScence.h"
#include "Game.h"

CBulletFireMario::CBulletFireMario(int d)
{
	direction = d;
	SetState(BULLET_FLY_ANI);
}

void CBulletFireMario::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + BULLET_BBOX_WIDTH;
	bottom = y + BULLET_BBOX_HEIGHT;
}
void CBulletFireMario::HandleDeteleItem()
{
	CMario *mario = dynamic_cast<CPlayScene *>(CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	float marioX, marioY;
	mario->GetPosition(marioX, marioY);
	float b = abs(marioY - y);
	float a = abs(marioX - x);
	if (a > NUMBER_250 || b > NUMBER_250)
	{
		SetStateObjectDelete(1);
		mario->SubCountBullet();
	}
}

void CBulletFireMario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	DWORD now = GetTickCount();
	CGameObject::Update(dt, coObjects);
	if (now - timeChangeDirection > BULLET_MARIO_FIRE_TIME_CHANGE_DIRECTION && timeChangeDirection != 0)
		vy = BULLET_MARIO_FIRE_SPEED_Y;
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
		if (nx != 0)
			vx = 0;
		if (ny != 0)
			vy = 0;
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{

			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CBrickFloor *>(e->obj))
			{
				Collisions(e);
			}
			if (dynamic_cast<CHold *>(e->obj))
			{
				Collisions(e);
			}
			if (dynamic_cast<CBrickColliBroken *>(e->obj))
			{
				Collisions(e);
			}
			if (dynamic_cast<CGoomba *>(e->obj))
			{
				CollisionGoomba(e);
			}
			if (dynamic_cast<CTurtle*>(e->obj))
			{
				CollisionTurtle(e);
			}
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];

	HandleDeteleItem();
}

void CBulletFireMario::Collisions(LPCOLLISIONEVENT e)
{
	if (e->ny < 0)
	{
		timeChangeDirection = GetTickCount();
		vy = -BULLET_MARIO_FIRE_SPEED_Y;
	}
	if (e->nx != 0)
	{
		SetStateObjectDelete(1);
		CMario *mario = dynamic_cast<CPlayScene *>(CGame::GetInstance()->GetCurrentScene())->GetPlayer();
		mario->SubCountBullet();
	}
}

void CBulletFireMario::CollisionGoomba(LPCOLLISIONEVENT c)
{
	// coding
	CGoomba *goomba = dynamic_cast<CGoomba *>(c->obj);
	// DebugOut(L"collision goomba:%d \n",c->nx);
	goomba->SetState(GOOMBA_STATE_START_DIE_COLLISION_TURTLR);
	goomba->SetTimeChangeDirection(GetTickCount());
	float xGomba, yGomba;
	goomba->GetPosition(xGomba, yGomba);
	if (x > xGomba)
		goomba->SetDirectionCollition(false);
	if (x < xGomba)
		goomba->SetDirectionCollition(); // default true
	SetStateObjectDelete(1);
}

void CBulletFireMario::CollisionTurtle(LPCOLLISIONEVENT c)
{
	CTurtle* turtle = dynamic_cast<CTurtle*>(c->obj);
	turtle->SetState(TURTLE_STATE_DIE_COLLISION_TAIL);
	turtle->SetTimeChangeDirection(GetTickCount());
	float xTurtle, yTurtle;
	turtle->GetPosition(xTurtle, yTurtle);
	if (x > xTurtle)
	{
		turtle->SetDirectionCollition(false);
	}
	if (x < xTurtle) {
		turtle->SetDirectionCollition(); // default true
	}
	SetStateObjectDelete(1);
}

void CBulletFireMario::Render()
{
	int ani = BULLET_FLY_ANI;
	animation_set->at(ani)->Render(x, y);
	// RenderBoundingBox();
}

void CBulletFireMario::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BULLET_FLY_ANI:
		vx = BULLET_MARIO_FIRE_SPEED_X;
		if (direction < 0)
			vx = -BULLET_MARIO_FIRE_SPEED_X;
		vy = BULLET_MARIO_FIRE_SPEED_Y;
		break;
	}
}
