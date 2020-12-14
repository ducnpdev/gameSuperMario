#include "Turtle.h"
#include "Game.h"
CTurtle::CTurtle(int type) {
	turtleTypeRender = type;
	type = OBJECT_TYPE_TURTLE;
	SetState(TURTLE_STATE_WALKING_LEFT);
	// turtleTypeRender = typeTurtleRender;
}
void CTurtle::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	CGameObject::Update(dt, coObjects);
	vy = 0.007f * dt;
	
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
		if (state == TURTLE_STATE_DIE) {
			vx = 0;
		}
		if (x < BORDER_LEFT && state == TURTLE_STATE_WALKING_LEFT) {
			SetState(TURTLE_STATE_WALKING_RIGHT);
		}
		if (x > BORDER_RIGHT && state == TURTLE_STATE_WALKING_RIGHT) {
			SetState(TURTLE_STATE_WALKING_LEFT);
		}
		// loop collision 
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CBrickFloor*>(e->obj))
			{
				if (e->nx < 0) {
					//DebugOut(L"1111\n");
					vx = -TURTLE_WALKING_SPEED_DIE;
				}
				else if (e->nx > 0){
					//DebugOut(L"2222\n");
					
					vx = TURTLE_WALKING_SPEED_DIE;
				}
			}
			if (dynamic_cast<CBrick*>(e->obj))
			{
				if (e->nx < 0) {

					vx = -TURTLE_WALKING_SPEED_DIE;
					CBrick* brick = dynamic_cast<CBrick*>(e->obj);
					if (brick->GetState() == BRICK_STATE_ANIMATION)
					{
						brick->SetState(BRICK_STATE_DIE);
						int type = brick->GetTypeItemRender();
						dynamic_cast<CMario*>(CGame::GetInstance()->GetCurrentScene())->renderItemCollisionBrick(type, brick->x, brick->y);
					}
				}

			}
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}
void CTurtle::Render() {
	int ani = -1;
	if (state == TURTLE_STATE_DIE) {
		ani = TURTLE_ANI_DIE;
	}
	if (state == TURTLE_STATE_WALKING_RIGHT) {
		ani = TURTLE_ANI_WALKING_RIGHT;
	}
	if (state == TURTLE_STATE_WALKING_LEFT) {
		ani = TURTLE_ANI_WALKING_LEFT;
	}
	
	if (state == TURTLE_STATE_DIE_MOVING_RIGHT || state == TURTLE_STATE_DIE_MOVING_LEFT) {
		ani = TURTLE_ANI_DIE;
	}
	animation_set->at(ani)->Render(x, y);
	// RenderBoundingBox();
}

void CTurtle::SetState(int state) {
	CGameObject::SetState(state);
	switch (state)
	{
	case TURTLE_STATE_DIE:
		y += TURTLE_BBOX_HEIGHT_BIG - TURTLE_BBOX_HEIGHT_SMAILL;
		vx = 0;
		vy = 0;
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
	}
}

void CTurtle::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = x;
	top = y;
	right = x + 15;
	bottom = y + 15;
	if (state == TURTLE_STATE_WALKING_LEFT || state == TURTLE_STATE_WALKING_RIGHT) {
		bottom = y + TURTLE_BBOX_HEIGHT_BIG;
	}
}