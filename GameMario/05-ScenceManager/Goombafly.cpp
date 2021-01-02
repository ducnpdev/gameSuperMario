#include "Goombafly.h"
CGoombafly::CGoombafly(float x, float y ) {
	goomba_fly_origin_x = x;
	goomba_fly_origin_y = y;
	jump_at = GetTickCount();
	type = OBJECT_TYPE_GOOMBA_FLY;
	SetState(GOOMBA_FLY_STATE_FLY);
	SetUntouchableGoombaFly(0);
}

void CGoombafly::Render() {
	int ani = -1;
	if (state == GOOMBA_FLY_STATE_FLY) {
		ani = GOOMBA_FLY_ANI_FLY;
	}
	if (state == GOOMBA_FLY_STATE_DIE) {
		ani = GOOMBA_FLY_ANI_DIE;
	}
	if (state == GOOMBA_FLY_STATE_WALKING) {
		ani = GOOMBA_FLY_ANI_WALKING;
	}
	if (state == GOOMBA_FLY_STATE_START_DIE_COLLISION_TURTLR) {
		ani = GOOMBA_FLY_ANI_DIE_COLLISION;
	}
	animation_set->at(ani)->Render(x, y);
	// RenderBoundingBox();
}

void CGoombafly::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	CGameObject::Update(dt, coObjects);
	DWORD now = GetTickCount();
	// touchable 
	if (GetTickCount() - untouchableGoombaFly_start > TIME_GOOMBA_FLY_UNTOUCHABLE) {
		untouchableGoombaFly = Touchable;
		untouchableGoombaFly_start = NumberZero;
	}
	// jump interval
	if (GetTickCount() > jump_at + GOOMBA_FLY_JUMP_INTERVAL) {
		if (GetState() == GOOMBA_FLY_STATE_FLY) {
				DebugOut(L"jumpjump \n");

			jump();
		}
	}

	// Simple fall down
	vy += GOOMBA_FLY_GRAVITY * dt;

	if (now - timeChangeDirection < GOOMBA_TIME_CHANGE_DIRECTION && timeChangeDirection != NUMBER_0)
	{
		vy = -GOOMBA_SPEED_CHANGE_DIRECTION;
	}

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	
	coEvents.clear();
	// turn off collision when die 
	float min_tx, min_ty, nx = 0, ny;
	float rdx = 0;
	float rdy = 0;
	if (state == GOOMBA_FLY_STATE_FLY || state == GOOMBA_FLY_STATE_WALKING) {
		CalcPotentialCollisions(coObjects, coEvents);
	}
	FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
	// No collision occured, proceed normally
	if (coEventsResult.size() == 0)
	{
		x += dx;
		y += dy;
		//if(state != GOOMBA_FLY_STATE_WALKING) calculateVx();
	}
	else
	{
		// block every object first!
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;
		
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CTurtle *>(e->obj))
			{
				SetState(GOOMBA_FLY_STATE_START_DIE_COLLISION_TURTLR);
				timeChangeDirection = GetTickCount();
			}
			if (dynamic_cast<CBrick*>(e->obj))
			{
				if (e->nx < 0)
					vx = -GOOMBA_FLY_WALKING_SPEED;
				if (e->nx > 0)
					vx = GOOMBA_FLY_WALKING_SPEED;
			}
		}
	}
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}
void CGoombafly::SetState(int state) {
	CGameObject::SetState(state);
	switch (state)
	{
		case GOOMBA_FLY_STATE_DIE:
			y += GOOMBA_FLY_BBOX_HEIGHT - GOOMBA_FLY_BBOX_HEIGHT_DIE + 1;
			vx = 0;
			break;
		case GOOMBA_FLY_STATE_WALKING: 
			vx = -GOOMBA_FLY_WALKING_SPEED
			break;
		case GOOMBA_FLY_STATE_FLY: 
			vx = -GOOMBA_FLY_WALKING_SPEED;
			break;
		case GOOMBA_FLY_STATE_START_DIE_COLLISION_TURTLR:
			if(!directionCollition) {
				vx = -GOOMBA_FLY_DIE_SPEED_VX;
			}else {
				vx = GOOMBA_FLY_DIE_SPEED_VX;
			}
			vy = -GOOMBA_FLY_DIE_SPEED;
			break;	
	}
}

void CGoombafly::GetBoundingBox(float& left, float& top, float& right, float& bottom){
	left = x;
	top = y;
	right = x + GOOMBA_FLY_BBOX_WIDTH;
	if (state == GOOMBA_FLY_STATE_DIE)
		bottom = y + GOOMBA_FLY_BBOX_HEIGHT_DIE;
	else if(state == GOOMBA_FLY_STATE_WALKING)
		bottom = y + GOOMBA_FLY_BBOX_HEIGHT;
	else 
		bottom = y + GOOMBA_FLY_BBOX_HEIGHT_FLY;
}
void CGoombafly::jump()
{
	SetState(GOOMBA_FLY_STATE_FLY);
	vy -= GOOMBA_FLY_SPEED_Y;
	jump_at = GetTickCount();
}

void CGoombafly::calculateVx()
{
	//SetState(GOOMBA_FLY_STATE_FLY);

	if (x < 20) {
		direction = 1;
	}
	if (x > 300) {
		direction = -1;
	}
	vx = direction * GOOMBA_FLY_WALKING_SPEED;
}

void CGoombafly::SetUntouchableGoombaFly(int untouchableGoombaFly)
{
	this->untouchableGoombaFly = untouchableGoombaFly;
}

int CGoombafly::GetUntouchableGoombaFly()
{
	return this->untouchableGoombaFly;
}

void CGoombafly::StartUntouchableGoombaFly()
{
	untouchableGoombaFly = UnTouchable;
	untouchableGoombaFly_start = GetTickCount();
}
