#include "Letter.h"

CLetter::CLetter()
{
}

void CLetter::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
}

void CLetter::Render()
{
	int ani = 0;
    animation_set->at(ani)->Render(x, y);
	// RenderBoundingBox();
}

void CLetter::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
    left = x;
	top = y;
	right = x + NUMBER_10;
	bottom = y + NUMBER_10;
}

void CLetter::SetState(int state)
{
	CGameObject::SetState(state);
}
