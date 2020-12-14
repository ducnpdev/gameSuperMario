#include "Number.h"
#include "Hud.h"


CNumber::CNumber(float x, float y) {
	origin_x = x;
	origin_y = y;
	// type = OBJECT_TYPE_NUMBER;
	SetState(NUMBER_STATE_FLY);
	NUMBER_TIME_START = GetTickCount();
}

void CNumber::Render() {

	animation_set->at(0)->Render(x, y);
	// RenderBoundingBox();
}

void CNumber::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	CGameObject::Update(dt, coObjects);
	x += dx;
	y += dy;
	if (GetTickCount() - NUMBER_TIME_START < NUMBER_1000) {
		if (y < origin_y - NUMBER_POSITION_MOVEMENT) {
			vy = -vy;
		}
		if (y > origin_y) {
			vy = -vy;
		}
	}
	else {
		SetStateObjectDelete(NUMBER_1);
		CHud::GetInstance()->AddNumberMoney(NUMBER_100);
	}
}

void CNumber::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	left = x;
	top = y;
	right = x + NUMBER_BBOX_WIDTH;
	bottom = y + NUMBER_BBOX_HEIGHT;
}

void CNumber::SetState(int state) {
	CGameObject::SetState(state);
	switch (state) {
	case NUMBER_STATE_FLY:
		vy = -NUMBER_FLY_SPEED;
		break;
	default:
		break;
	}
}
void CNumber::SetStateDie(int stateDie) {
	CGameObject::SetStateDie(stateDie);
}