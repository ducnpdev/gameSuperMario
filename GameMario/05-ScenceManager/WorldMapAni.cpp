#include "WorldMapAni.h"
CWorldMapAni::CWorldMapAni(int type) {
	// origin_x = x;
	// origin_y = y;
	typeRender = type;
	initTime = GetTickCount();
	SetState(WORLD_MAP_STATE_INIT);
}

void CWorldMapAni::Render() {
	int ani = 0;
	if (typeRender == 0) {
		ani = WORLD_MAP_ANI_MOVING;
	}
	if (typeRender == 1) {
		ani = WORLD_MAP_ANI_DOOR1;
	}
	if (typeRender == 2) {
		ani = WORLD_MAP_ANI_DOOR2;
	}
	if (typeRender == 3) {
		ani = WORLD_MAP_ANI_DOOR3;
	}
	if (typeRender == 4) {
		ani = WORLD_MAP_ANI_DOOR4;
	}
	if (typeRender == 5) {
		ani = WORLD_MAP_ANI_DOOR5;
	}
	if (typeRender == 6) {
		ani = WORLD_MAP_ANI_DOOR6;
	}
	if (typeRender == 7) {
		ani = WORLD_MAP_ANI_WORD_HELP;
	}
	if (typeRender == 8) {
		ani = WORLD_MAP_ANI_ENEMIES_MOVE_LEFT;
	}
	if (typeRender == 10) {
		ani = WORLD_MAP_ANI_CASINO;
	}
	if (typeRender == 11) {
		ani = WORLD_MAP_ANI_START;
	}
	if (typeRender == 12) {
		ani = WORLD_MAP_ANI_CAU;
	}
	animation_set->at(ani)->Render(x, y);
	// RenderBoundingBox();
}



void CWorldMapAni::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	CGameObject::Update(dt, coObjects);
	//vy = 0.05f;
	// y += dy;
 	// x += dx;
	// // DebugOut(L"Leaf %f: \n", x);
	// if (x > origin_x + 10) {
	// 	SetState(INTRO_LEAF_STATE_DIRECTION_NAGETIVE);
	// }
	// if (x < origin_x - 10) {
	// 	SetState(INTRO_LEAF_STATE_INIT);
	// }
}

void CWorldMapAni::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	left = x;
	top = y;
	right = x + 16;
	bottom = y + 16;
}

void CWorldMapAni::SetState(int state) {
	CGameObject::SetState(state);
	switch (state) {
	/*case WORLD_MAP_STATE_INIT:
		vy = 0.0f;
		vx = 0.0f;
		break;*/
	/*case INTRO_LEAF_STATE_DIRECTION_NAGETIVE:
		vy = 0.05f;
		vx = -0.05f;
		break;*/
		//vx = -0.05f;
	default:
		break;
	}
}
