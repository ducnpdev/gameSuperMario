#include "Square.h"
CSquare::CSquare() {
	type = OBJECT_TYPE_SQUARE;
}

void CSquare::Render() {
	animation_set->at(0)->Render(x, y);
}

void CSquare::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = x;
	top = y;
	right = x + BRICK_FLOOR_BOX_WIDTH;
	bottom = y + BRICK_FLOOR_BOX_HEIGHT;
}