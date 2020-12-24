#include "MarioWorldMap.h"

CMarioWorldMap::CMarioWorldMap()
{
    marioWorldMapLevel = WORLD_MAP_MARIO_LEVEL_1;
    SetState(WORLD_MAP_MARIO_LEVEL1_STATE_IDLE);
}

void CMarioWorldMap::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
    left = x;
	top = y;
	right = x + 14;
	bottom = y + 14;
}

void CMarioWorldMap::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{	

    CGameObject::Update(dt);
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
	/*	x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;
		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;*/
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CPortal*>(e->obj)) {
				x += dx;
				y += dy;
			}
		}
	}
	
	if (state == WORLD_MAP_MARIO_SWITCH_SCENE) {
		vector<LPGAMEOBJECT> colidingPortalObjects;
		isCollidingObject(coObjects, colidingPortalObjects);
		for (UINT i = 0; i < colidingPortalObjects.size(); i++)
		{
			// DebugOut(L"WORLD_MAP_MARIO_SWITCH_SCENE \n");
			LPGAMEOBJECT c = colidingPortalObjects[i];
			if (dynamic_cast<CPortal*>(c)) {
				CPortal* p = dynamic_cast<CPortal*>(c);
				CGame::GetInstance()->SwitchScene(p->GetSceneId());
			}
		}
	}


	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
   //
}

void CMarioWorldMap::Render()
{
    int ani = WORLD_MAP_MARIO_LEVEL1_ANI_IDLE;
    int alpha = 255;
	if (untouchable)
		alpha = 128;
	animation_set->at(ani)->Render(x, y, alpha);
	// RenderBoundingBox();
}

void CMarioWorldMap::SetState(int state)
{
	CGameObject::SetState(state);
    switch (state)
	{
    case WORLD_MAP_MARIO_LEVEL1_STATE_IDLE:
        vx = 0.0f;
        vy = 0.0f;
        break;
    case WORLD_MAP_MARIO_LEVEL1_STATE_WALKING_RIGHT:
        vy = 0.0f;
		vx = 0.05f;
        break;
    case WORLD_MAP_MARIO_LEVEL1_STATE_WALKING_LEFT:
        vx = -0.05f;
        vy = 0.0f;
        break;
	case WORLD_MAP_MARIO_LEVEL1_STATE_WALKING_DOWN:
		vx = 0.0f;
		vy = 0.05f;
		break;
	case WORLD_MAP_MARIO_LEVEL1_STATE_WALKING_UP:
		vx = 0.0f;
		vy = -0.05f;
		break;
    default:
		break;
    }

}

void CMarioWorldMap::isCollidingObject(vector<LPGAMEOBJECT>* coObjects, vector<LPGAMEOBJECT>& colidingObjects)
{	
	float otherL;
	float otherT;
	float otherB;
	float otherR;

	float objectL;
	float objectT;
	float objectB;
	float objectR;
	GetBoundingBox(objectL, objectT, objectR, objectB);
	for (int i = 0; i < coObjects->size(); i++) {
		coObjects->at(i)->GetBoundingBox(otherL, otherT, otherR, otherB);
		if (otherL <= objectR &&
			otherR >= objectL &&
			otherT <= objectB &&
			otherB >= objectT) {
			colidingObjects.push_back(coObjects->at(i));
		}
	}
}
