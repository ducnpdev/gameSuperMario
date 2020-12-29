#include "Tail.h"
#include "Goombafly.h"
#include "Goomba.h"
#include "Flower.h"

CTail::CTail()
{
	// damageLevel = ITEM_DAMAGE_LEVEL_1;
	type = OBJECT_TYPE_TAIL;
	CAnimationSets *animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(OBJECT_TYPE_TAIL);
	SetAnimationSet(ani_set);
	isActive = false;
	activeAt = 0;
}

void CTail::SetActive(bool _isActive)
{
	if (isActive && _isActive)
	{
		return;
	}

	isActive = _isActive;
	if (_isActive)
	{
		activeAt = GetTickCount();
	}
}

void CTail::Render()
{
	if (isActive)
	{
		animation_set->at(0)->Render(x, y);
		RenderBoundingBox();
	}
}

void CTail::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (isActive)
	{
		CGameObject::Update(dt);
		if (GetTickCount() - activeAt > MARIO_WITH_TAIL_ATTACK_TIME)
		{
			SetActive(false);
		}
		vector<LPGAMEOBJECT> colidingObjects;
		isCollidingObject(coObjects, colidingObjects);
		for (UINT i = 0; i < colidingObjects.size(); i++)
		{
			LPGAMEOBJECT c = colidingObjects[i];
			if (dynamic_cast<CBrickColliBroken *>(c))
			{
				CBrickColliBroken *brickColliBroken = dynamic_cast<CBrickColliBroken *>(c);
				float x, y;
				brickColliBroken->GetPosition(x, y);
				int type = brickColliBroken->GetType();
				if (type == NUMBER_3) {	
					brickColliBroken->SetState(BRICK_COLLISION_BROKENT_NOT_COLLISION);
					if (brickColliBroken->GetAllowRenderItem()) {
						dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene())->GetPlayer()->renderItemCollisionBrick(5, x, y - 16);
						brickColliBroken->SetAllowRenderItem();
					}
				}
				if (type == 1 && !brickColliBroken->GetActiveGold()) {
					dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene())->GetPlayer()->renderItemCollisionBrick(6, x, y );
					brickColliBroken->tailDeleteObj = true;
				}
			}
		}
	}
}

void CTail::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
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

void CTail::isCollidingObject(vector<LPGAMEOBJECT> *coObjects, vector<LPGAMEOBJECT> &colidingObjects)
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
	for (int i = 0; i < coObjects->size(); i++)
	{
		coObjects->at(i)->GetBoundingBox(otherL, otherT, otherR, otherB);
		if (otherL <= objectR &&
			otherR >= objectL &&
			otherT <= objectB &&
			otherB >= objectT)
		{
			colidingObjects.push_back(coObjects->at(i));
		}
	}
}

void CTail::RenderItem(float x, float y)
{
	CAnimationSets *animation_sets = CAnimationSets::GetInstance();
	CGameObject *obj = NULL;
	for (int i = 1; i <= 4; i++) {
		obj = new CItemFly(i);
		obj->SetPosition(x, y);
		LPANIMATION_SET ani_set = animation_sets->Get(88);
		obj->SetAnimationSet(ani_set);
		dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene())->AddObject(obj);
	}
}

void CTail::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + TAIL_WIDTH_BOUNDING_BOX;
	bottom = y + TAIL_HEIGHT_BOUNDING_BOX;
	/*if (damageLevel == ITEM_DAMAGE_LEVEL_2)
	{
		right = x + ITEM_DAMAGE_BOX_WIDTH_l2;
	}
	else if (damageLevel == ITEM_DAMAGE_LEVEL_3)
	{
		right = x + ITEM_DAMAGE_BOX_WIDTH_l3;
	}*/
}
