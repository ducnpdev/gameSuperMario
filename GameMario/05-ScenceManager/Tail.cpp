#include "Tail.h"
#include "Goombafly.h"
#include "Goomba.h"
#include "Flower.h"
CTail::CTail()
{
	damageLevel = ITEM_DAMAGE_LEVEL_1;
	type = OBJECT_TYPE_TAIL;
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(OBJECT_TYPE_TAIL);
	SetAnimationSet(ani_set);
	isActive = false;
	activeAt = 0;
}

void CTail::SetActive(bool _isActive) {
	if (isActive && _isActive) {
		return;
	}

	isActive = _isActive;
	if (_isActive) {
		activeAt = GetTickCount();
	}
}

void CTail::Render()
{
	if (isActive) {
		animation_set->at(0)->Render(x, y);
		RenderBoundingBox();
	}
}

void CTail::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isActive) {
		CGameObject::Update(dt);
		if (GetTickCount() - activeAt > MARIO_WITH_TAIL_ATTACK_TIME) {
			SetActive(false);
		}
		vector<LPGAMEOBJECT> colidingObjects;
		isCollidingObject(coObjects, colidingObjects);
		for (UINT i = 0; i < colidingObjects.size(); i++)
		{
			LPGAMEOBJECT c = colidingObjects[i];
			
			c->tailDeleteObj = true;
		}
	}
}

void CTail::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state) {
	case ITEMDAMAGE_STATE_DIE:
		vy = 0;
		vx = 0;
		break;
	case ITEMDAMAGE_STATE_NORMAL:
		break;
	default:
		break;
	}
}

void CTail::isCollidingObject(vector<LPGAMEOBJECT>* coObjects, vector<LPGAMEOBJECT>& colidingObjects)
{
	float otherL;
	float otherT;
	float otherB;
	float otherR;

	float objectL;
	float objectT;
	float objectB;
	float objectR;
	GetBoundingBox(objectL, objectT, objectR, objectB);
	for (int i = 0; i < coObjects->size(); i++) {
		coObjects->at(i)->GetBoundingBox(otherL, otherT, otherR, otherB);
		if (otherL <= objectR &&
			otherR >= objectL &&
			otherT <= objectB &&
			otherB >= objectT) {
			colidingObjects.push_back(coObjects->at(i));
		}
	}
}

void CTail::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x; 
	top = y;
	right = x + ITEM_DAMAGE_BOX_WIDTH_l1;
	bottom = y + ITEM_DAMAGE_BOX_HEIGHT_l1;
	if(damageLevel == ITEM_DAMAGE_LEVEL_2){
		right = x + ITEM_DAMAGE_BOX_WIDTH_l2;
	}else if(damageLevel == ITEM_DAMAGE_LEVEL_3){
		right = x + ITEM_DAMAGE_BOX_WIDTH_l3;
	}
}
