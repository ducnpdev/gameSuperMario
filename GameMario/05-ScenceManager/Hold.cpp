
#include "Hold.h"

CHold::CHold(int width, int height)
{
   // type = OBJECT_TYPE_HOLD;
    widthBox = width;
    heightBox = height;
}

void CHold::Render()
{
    int ani = 0;
    animation_set->at(ani)->Render(x, y);
   // RenderBoundingBox();
}

void CHold::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
    left = x;
    top = y;
    right = x + widthBox;
    bottom = y + heightBox;
}
