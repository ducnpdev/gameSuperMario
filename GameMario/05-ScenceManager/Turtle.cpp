#include "Turtle.h"
#include "Game.h"

CTurtle::CTurtle(int type, float x, float y)
{
	turtleTypeRender = type;
	// type = OBJECT_TYPE_TURTLE;
	SetState(TURTLE_STATE_WALKING_LEFT);
	originX = x; originY = y;

}
void CTurtle::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	DebugOut(L"y: %f", y);
	DWORD now = GetTickCount();
	if (state == TURTLE_STATE_DIE && now - timeoutRelive > 5000 && timeoutRelive != 0) {
		SetState(TURTLE_STATE_TIME_OUT_RELIVE);
		timeRelive = now;
	}
	if (now - timeRelive > 500 && timeRelive != 0 && state == TURTLE_STATE_TIME_OUT_RELIVE) {
		float a, b; GetPosition(a, b);
		
		SetPosition(a, b - 20);
		SetState(TURTLE_STATE_WALKING_LEFT);
	}
	// DebugOut(L"state: %d \n", state);
	CGameObject::Update(dt, coObjects);

	vy = 0.009f * dt;
	if (state == TURTLE_STATE_DIE) vx = 0;
	if (turtleTypeRender == 1)
	{
		if (x < BORDER_LEFT && state == TURTLE_STATE_WALKING_LEFT && y < 120)
		{
			SetState(TURTLE_STATE_WALKING_RIGHT);
			//vx = 0.03f;
		}
		if (x > BORDER_RIGHT && state == TURTLE_STATE_WALKING_RIGHT && y < 120)
		{

			SetState(TURTLE_STATE_WALKING_LEFT);
			//vx = -0.03f;
		}
	}

	// turtle 2 tren bricjbroken
	if (turtleTypeRender == NUMBER_2)
	{
		if (x < 2085 && state == TURTLE_STATE_WALKING_LEFT)
		{
			SetState(TURTLE_STATE_WALKING_RIGHT);
			//vx = 0.03f;
		}
		if (x > 2105 && state == TURTLE_STATE_WALKING_RIGHT)
		{
			SetState(TURTLE_STATE_WALKING_LEFT);
			//vx = -0.03f;
		}
	}

	if (now - timeChangeDirection < 300 && timeChangeDirection != NUMBER_0) // timeChangeDirection when collision with tail
	{
		vy = -0.1f;
	}

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();
	// turn off collision when die
	float min_tx, min_ty, nx = 0, ny;
	float rdx = 0;
	float rdy = 0;

	CalcPotentialCollisions(coObjects, coEvents);
	FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
	// No collision occured, proceed normally
	if (coEventsResult.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 1.0f;
		if (ny != 0) vy = 0;

		// loop collision
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CBrickFloor *>(e->obj))
			{
				if (e->nx < 0)
				{
					if(state == TURTLE_STATE_WALKING_RIGHT) SetState(TURTLE_STATE_WALKING_LEFT);
					else { vx = -TURTLE_WALKING_SPEED_DIE; }
				}
				else if (e->nx > 0)
				{
					if (state == TURTLE_STATE_WALKING_LEFT) SetState( TURTLE_STATE_WALKING_RIGHT);
					else { vx = TURTLE_WALKING_SPEED_DIE; }
				}
			}
			if (dynamic_cast<CBrick *>(e->obj))
			{
				if (e->nx < 0)
				{
					vx = -TURTLE_WALKING_SPEED_DIE;
					CBrick *brick = dynamic_cast<CBrick *>(e->obj);
					if (brick->GetState() == BRICK_STATE_ANIMATION)
					{
						brick->SetState(BRICK_STATE_DIE);
						int type = brick->GetTypeItemRender();
						dynamic_cast<CMario *>(CGame::GetInstance()->GetCurrentScene())->renderItemCollisionBrick(type, brick->x, brick->y);
					}
				}
			}
			if (dynamic_cast<CBrickColliBroken *>(e->obj))
			{
				CBrickColliBroken *brickColliBroken = dynamic_cast<CBrickColliBroken *>(e->obj);
				if (e->nx < 0)
				{
					SetState(TURTLE_STATE_DIE_MOVING_LEFT);
					brickColliBroken->SetStateObjectDelete(NUMBER_1);
				}
				else if (e->nx > 0)
				{
					SetState(TURTLE_STATE_DIE_MOVING_RIGHT);
					brickColliBroken->SetStateObjectDelete(NUMBER_1);
				}
			}
			/* if(dynamic_cast<CGoomba*>(e->obj)){
			 	DebugOut(L"turtle collision with Goomba \n");
			 }*/
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];
}
void CTurtle::Render()
{
	int ani = 0;
	if (state == TURTLE_STATE_DIE || state == TURTLE_STATE_DIE_IDLE)
	{
		ani = TURTLE_ANI_DIE;
	}
	if (state == TURTLE_STATE_WALKING_RIGHT)
	{
		ani = TURTLE_ANI_WALKING_RIGHT;
	}
	if (state == TURTLE_STATE_WALKING_LEFT)
	{
		ani = TURTLE_ANI_WALKING_LEFT;
	}

	if (state == TURTLE_STATE_DIE_MOVING_RIGHT || state == TURTLE_STATE_DIE_MOVING_LEFT)
	{
		ani = TURTLE_ANI_DIE_MOVING; // fix ani
	}
	if (state == TURTLE_STATE_DIE_COLLISION_TAIL)
	{
		ani = TURTLE_ANI_DIE_COLLISION_TAIL;
	}
	if (state == TURTLE_STATE_TIME_OUT_RELIVE) {
		ani = TURTLE_ANI_TIME_OUT_RELIVE;
	}
	animation_set->at(ani)->Render(x, y);
	// RenderBoundingBox();
}

void CTurtle::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case TURTLE_STATE_DIE_IDLE:
		vx = 0;
		break;
	case TURTLE_STATE_TIME_OUT_RELIVE:
		vx = 0;
		break;
	case TURTLE_STATE_DIE:
		vx = NUMBER_0;
		vy = NUMBER_0;
		break;
	case TURTLE_STATE_WALKING_LEFT:
		vx = -TURTLE_WALKING_SPEED;
		break;
	case TURTLE_STATE_WALKING_RIGHT:
		vx = TURTLE_WALKING_SPEED;
		break;
	case TURTLE_STATE_DIE_MOVING_RIGHT:
		vx = TURTLE_WALKING_SPEED_DIE;
		break;
	case TURTLE_STATE_DIE_MOVING_LEFT:
		vx = -TURTLE_WALKING_SPEED_DIE;
		break;
	case TURTLE_STATE_DIE_COLLISION_TAIL:
		vy = -0.05f;
		if (!directionCollition)
		{
			vx = -0.08f;
		}
		else
		{
			vx = 0.08f;
		}
		break;
	}
}

void CTurtle::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + TURTLE_WIDTH_BOUNDING_BOX;
	bottom = y + TURTLE_HEIGHT_DIE_WALKING_BOUNDING_BOX;
	if (state == TURTLE_STATE_WALKING_LEFT || state == TURTLE_STATE_WALKING_RIGHT)
	{
		bottom = y + TURTLE_HEIGHT_WALKING_BOUNDING_BOX;
	}
}