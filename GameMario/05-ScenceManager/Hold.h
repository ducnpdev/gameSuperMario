#pragma once
#include "GameObject.h"
#include "Define.h"
class CHold : public CGameObject
{
    bool WidthOrHeight = false; // false is wall with width
    int widthBox;
    int heightBox;
public:
    CHold(int width, int height);
    virtual void Render();
    virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
    //virtual void SetState(int state);
};

