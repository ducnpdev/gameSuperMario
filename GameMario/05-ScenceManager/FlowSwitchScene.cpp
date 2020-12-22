#include "FlowSwitchScene.h"

CFlowSwitchScene::CFlowSwitchScene()
{
    SetState(FLOW_SWITCH_SCENE_STATE_IDLE);
}

void CFlowSwitchScene::Render()
{
    int ani = 0;
    animation_set->at(ani)->Render(x, y);
   // RenderBoundingBox();

}

void CFlowSwitchScene::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
    left = x;
    top = y;
    right = x + NUMBER_16;
    bottom = y + NUMBER_16;
}

void CFlowSwitchScene::SetState(int state)
{
    CGameObject::SetState(state);
	switch (state) {
	case FLOW_SWITCH_SCENE_STATE_IDLE:
        vx = 0.0f;
        vy = 0.0f;
		break;
	case FLOW_SWITCH_SCENE_STATE_FLY:
        vx = 0.0f;
        vy = -0.3f;
		break;
	default:
		break;
	}
}

void CFlowSwitchScene::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
    CGameObject::Update(dt, coObjects);
    y += dy;
    x += dx;
}
