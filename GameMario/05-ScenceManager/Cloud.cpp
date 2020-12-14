#include "Cloud.h"

CCloud::CCloud() {
}

void CCloud::Render() {
	int ani = CLOUD_ANI;
	animation_set->at(ani)->Render(x,y);
}

void CCloud::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = x;
	top = y;
	right = x + CLOUD_BBOX_WIDTH;
	bottom = y + CLOUD_BBOX_HEIGHT;
}