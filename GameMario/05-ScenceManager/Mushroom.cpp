#include "Mushroom.h"
CMushroom::CMushroom() {
	// type = OBJECT_TYPE_MUSHROOM;
	SetState(MUSHROOM_STATE_WALKING);
}
void CMushroom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	if (state == MUSHROOM_STATE_WALKING) {
		vx = MUSHROOM_WALKING_SPEED;
	}
	CGameObject::Update(dt, coObjects);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();

	vy += MUSHROOM_GRAVITY * dt;
	CalcPotentialCollisions(coObjects, coEvents);
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else {
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		// how to push back Mario if collides with a moving objects, what if Mario is pushed this way into another object?
		//if (rdx != 0 && rdx!=dx)
		//	x += nx*abs(rdx); 

		// block every object first!
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) {
			vx = 0;
		} 
		if (ny != 0) {
			vy = 0;
		}
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CBrickFloor*>(e->obj)) {
				if (e->nx < 0) {
					 vx = -MUSHROOM_WALKING_SPEED;
					// DebugOut(L"vx:%f \n",vx);
				}
			}	
			/*if (dynamic_cast<CMario*>(e->obj)) {
				 DebugOut(L"Collision with brick floor \n");
			}*/

		}
	}

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}
void CMushroom::Render() {
	int ani = MUSHROOM_ANI_WALKING;
	animation_set->at(ani)->Render(x, y);
	// RenderBoundingBox();
}
void CMushroom::GetBoundingBox(float &left,float &top, float &right, float &bottom) {
	left = x;
	top = y;
	right = x + MUSHROOM_BBOX_WIDTH;
	bottom = y + MUSHROOM_BBOX_HEIGHT;
}
void CMushroom::SetState(int state) {
	CGameObject::SetState(state);
	switch (state)
	{
	case MUSHROOM_STATE_WALKING:
		vx = MUSHROOM_WALKING_SPEED;
		break;
	default:
		break;
	}
}