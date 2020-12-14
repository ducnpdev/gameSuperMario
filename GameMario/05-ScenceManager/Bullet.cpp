#include "Bullet.h"

CBullet::CBullet(int dirX, int dirY)
{
    directionX = dirX;
    directionY = dirY;
    type = OBJECT_TYPE_BULLET;
    SetState(BULLET_STATE_FLY);
}

void CBullet::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
    left = x;
    top = y;
    right = x + BULLET_BBOX_WIDTH;
    bottom = y + BULLET_BBOX_HEIGHT;
}

void CBullet::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
    CGameObject::Update(dt, coObjects);
    x += dx;
    y += dy;    
}

void CBullet::Render()
{
    int ani = BULLET_FLY_ANI;
    animation_set->at(ani)->Render(x, y);
    // RenderBoundingBox();
}

void CBullet::SetState(int state)
{
    CGameObject::SetState(state);
    switch (state)
    {
    case BULLET_STATE_FLY:
        if (directionX > 0) {
            vx = BULLET_FLY_SPEED_X;
            if (directionY > 0) {
                vy = BULLET_FLY_SPEED_Y;
            }
            else {
                vy = -BULLET_FLY_SPEED_Y;
            }
        }
        else {
            vx = -BULLET_FLY_SPEED_X;
            if (directionY > 0) {
                vy = BULLET_FLY_SPEED_Y;
            }
            else {
                vy = -BULLET_FLY_SPEED_Y;
            }
        }
        break;
    }
}
