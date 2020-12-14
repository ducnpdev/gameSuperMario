#include "Money.h"
#include "Hud.h"
#include "PlayScence.h"


CMoney::CMoney(float x, float y, bool checkMove ){
    isCheckMove = checkMove;
    origin_x = x;
    origin_y = y;
    SetState(MONEY_STATE_FLY);
    type = OBJECT_TYPE_MONEY;
    MONEY_TIME_START = GetTickCount();
}

void CMoney::GetBoundingBox(float &left, float &top, float &right, float &bottom){
    left = x;
    top = y;
    right = x + MONEY_BOX_WIDTH;
    bottom = y + MONEY_BOX_HEIGHT;
}

void CMoney::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects){
    CGameObject::Update(dt, coObjects);
   if (isCheckMove) {
        x += dx;
        y += dy;
        if (GetTickCount() - MONEY_TIME_START < 1000) {
            if (y < origin_y - MONEY_POSITION_MOVEMENT) {
                vy = -vy;
            }
            if (y > origin_y) {
                vy = -vy;
            }
        }
        else {
            SetStateObjectDelete(NUMBER_1);
            CAnimationSets* animation_sets = CAnimationSets::GetInstance();
            CGameObject* obj = NULL;
            obj = new CNumber(x, y);
            obj->SetPosition(x, y-NUMBER_10);
            LPANIMATION_SET ani_set = animation_sets->Get(OBJECT_TYPE_NUMBER);
            obj->SetAnimationSet(ani_set);
            dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene())->AddObject(obj);
            // CHud::GetInstance()->AddNumberMoney(NUMBER_100);
            CHud::GetInstance()->AddNumberGold(NUMBER_1);
        }
    }
  
}

void CMoney::Render(){
    int ani = MONEY_ANI_FLY;
    if(state == MONEY_STATE_DISAPPEAR){
        ani = MONEY_ANI_DISAPPEAR;
    }
    if (state == MONEY_STATE_DISAPPEAR) {
        ani = MONEY_ANI_DISAPPEAR;
    }
    animation_set->at(ani)->Render(x,y);
}

void CMoney::SetState(int state){
    CGameObject::SetState(state);
    switch (state) {
    case MONEY_STATE_FLY:
        vy = -MONEY_FLY_SPEED;
        break;
    case MONEY_STATE_DISAPPEAR:
        vy = 0;
        break;
    default: 
        break;
    }
}

void CMoney::SetMoneyPosition(float x, float y) {
    origin_x = x;
    origin_y = y;
}

void CMoney::isColidingObject(vector<LPGAMEOBJECT>* coObjects, vector<LPGAMEOBJECT>& colidingObjects) {
}   

void CMoney::SetStateDie(int stateDie) {
    CGameObject::SetStateDie(stateDie);
}