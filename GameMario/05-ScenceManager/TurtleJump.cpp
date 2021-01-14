#include "TurtleJump.h"


CTurtleJump::CTurtleJump() {
	jump_at = GetTickCount();
	SetState(TURTLE_JUMP_STATE_FLY);
	timeIntervalJump = GetTickCount();
}
void CTurtleJump::jump()
{
	vy = -0.02f;
	jump_at = GetTickCount();
}

void CTurtleJump::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	CGameObject::Update(dt, coObjects);
	DWORD now = GetTickCount();
	// if (now -  jump_at > TURTLE_JUMP_INTERVAL) {
	// 	if (GetState() == TURTLE_JUMP_STATE_FLY) {
	// 		jump();
	//  	}else{
	// 		vy = 0.02f ;
	// 	}
	// }
	if (GetState() == TURTLE_JUMP_STATE_FLY){
		if (now -  jump_at > 2000){
			vy = -0.005f;
 			jump_at = GetTickCount();
		}
		if (now -  jump_at <= 2000){
			vy = 0.2f;
			// jump_at = GetTickCount();
		}
	}else{
		vy = 0.05f * dt;
	}
//	DebugOut(L"vy %f \n",vy);
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
		// block every object first!
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) {
			vx = 0;
		}
		if (ny != 0) vy = 0;
	
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
		}
	}
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

}
void CTurtleJump::Render() {
	int ani = 0;
	if (state == TURTLE_JUMP_STATE_FLY) {
		ani = TURTLE_JUMP_ANI_FLY_LEFT;
	}
	if (state == TURTLE_JUMP_STATE_WALKING) {
		ani = TURTLE_JUMP_ANI_WALKING_LEFT;
	}
	if (state == TURTLE_JUMP_STATE_DIE) {
		ani = TURTLE_JUMP_ANI_DIE;
	}
	if (state == TURTLE_JUMP_STATE_DIE_MOVING_RIGHT || state == TURTLE_JUMP_STATE_DIE_MOVING_LEFT) {
		ani = TURTLE_JUMP_ANI_DIE_MOVING;
	}
	animation_set->at(ani)->Render(x, y);
	// RenderBoundingBox();
}

void CTurtleJump::SetState(int state) {
	CGameObject::SetState(state);
	switch (state)
	{
	case TURTLE_JUMP_STATE_FLY:
		vx = -TURTLE_JUMP_SPEED_VX;
		// vy = 0.5f;
		break;
	case TURTLE_JUMP_STATE_DIE:
		vy = 0.5f;
		vx = 0;
		break;
	case TURTLE_JUMP_STATE_WALKING:
		vx = -0.04f;
	//	vy = 0.5f;
		break;
	case TURTLE_JUMP_STATE_DIE_MOVING_RIGHT:
		vx = 0.15f;
		//vy = 0.5f;
		break;
	case TURTLE_JUMP_STATE_DIE_MOVING_LEFT:
		vx = -0.15f;
		break;
	}
}

void CTurtleJump::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = x;
	top = y;
	right = x + TURTLE_BBOX_WIDTH_BIG;
	if (state == TURTLE_JUMP_STATE_FLY) bottom = y + 27;
	else if (state == TURTLE_JUMP_STATE_WALKING) bottom = y + 27;
	else bottom = y + 15;
}