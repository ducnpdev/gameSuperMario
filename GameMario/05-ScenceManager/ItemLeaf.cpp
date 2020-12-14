#include "ItemLeaf.h"
CItemLeaf::CItemLeaf(float x, float y)
{
    origin_x = x;
    origin_y = y;
    SetState(LEAF_STATE_FLY);
    type = OBJECT_TYPE_LEAF;
    LEAF_TIME_START = GetTickCount();
}

void CItemLeaf::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects){
    CGameObject::Update(dt, coObjects);
    x += dx;
    y += dy;
   // DebugOut(L"PlayerSecond vx, vy: % \n", x);

    // if (vx < 0 && x < 0) { x = 10; vx = -vx; }
    // if (vx > 0 && x > 290) { x = 290; vx = -vx; }
    //if(GetTickCount() - )
    if (GetTickCount() - LEAF_TIME_START < LEAF_TIME) {
      
        if (y < origin_y - LEAF_POSITION_MOVEMENT) {
            vy = -vy;
            vx = LEAF_FLY_SPEED;
            LEAF_TIME_START_X = GetTickCount();
        }
        if ( GetTickCount() - LEAF_TIME_START_X > TIME_FLY_LEAF) {
            LEAF_TIME_START_X = GetTickCount();
            vx = -vx;
        }
    }
    else {
        SetState(STATE_MONEY_DIE);
    }
    
}

void CItemLeaf::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
    left = x;
    top = y;
    right = x + LEAF_BOX_WIDTH;
    bottom = y + LEAF_BOX_HEIGHT;
}
void CItemLeaf::Render()
{
    int ani = LEAF_ANI_FLY;
    if (state == LEAF_STATE_DISAPPEAR)
    {
        ani = LEAF_ANI_DISAPPEAR;
    }
    animation_set->at(ani)->Render(x, y);
   // RenderBoundingBox();
}
void CItemLeaf::SetState(int state){
    CGameObject::SetState(state);
    switch (state) {
    case LEAF_STATE_FLY:
        vy = -LEAF_FLY_SPEED;
        break;
    case LEAF_STATE_DISAPPEAR:
        vy = 0;
        break;
    default: 
        break;
    }
}

void CItemLeaf::SetStateDie(int stateDie) {
    CGameObject::SetStateDie(stateDie);
}