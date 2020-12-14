#include "BrickFloor.h"

CBrickFloor::CBrickFloor(int width,int height) {
	widthBox = width;
	heightBox = height;
	type = OBJECT_TYPE_BRICK_FLOOR;
}
void CBrickFloor::Render() {
	animation_set->at(0)->Render(x,y);
	// RenderBoundingBox();
}

void CBrickFloor::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	left = x; 
	top = y;
	right = x + widthBox;
	bottom = y + heightBox;
}