#include <algorithm>
#include "Utils.h"
#include <assert.h>
#include "Utils.h"
#include "Mario.h"
#include "Game.h"
#include "Goomba.h"
#include "Portal.h"
#include "Define.h"
#include "MorningStar.h"
#include "TurtleJump.h"
#include "Money.h"
#include "PlayScence.h"
#include "ItemLeaf.h"

CMario::CMario(float x, float y) : CGameObject()
{
	level = MARIO_LEVEL_3;
	untouchable = 0;
	SetState(MARIO_STATE_IDLE);
	start_x = x;
	start_y = y;
	this->x = x;
	this->y = y;
	second = GetTickCount();
	tail = new CTail();
	dynamic_cast<CPlayScene *>(CGame::GetInstance()->GetCurrentScene())
		->AddObject(tail);
}

void CMario::HandleAttack()
{
	if (level == MARIO_LEVEL_3)
	{
		if (checkAttact)
		{
			swingTailAttack();
			if (GetTickCount() - timeAttact > TIME_RESET_ACTTACK)
			{
				timeAttact = 0;
				checkAttact = false;
			}
		}
	}
}

void CMario::swingTailAttack()
{
	tail->SetActive();
	if (checkAttact && GetTickCount() - timeAttact < MARIO_WITH_TAIL_ATTACK_TIME / 2)
	{
		if (nx > 0)
		{
			tail->SetPosition(x - DEVIATION_ATTACK_BEHIND_X, y + DEVIATION_ACTTACK_Y);
		}
		else
		{
			tail->SetPosition(x + DEVIATION_ATTACK_FRONT_X, y + DEVIATION_ACTTACK_Y);
		}
	}
	else
	{
		if (nx > 0)
		{
			tail->SetPosition(x + DEVIATION_ATTACK_FRONT_X, y + DEVIATION_ACTTACK_Y);
		}
		else
		{
			tail->SetPosition(x - DEVIATION_ATTACK_BEHIND_X, y + DEVIATION_ACTTACK_Y);
		}
	}
}

void CMario::downLevel()
{
	if (untouchable == 0)
	{
		if (level == MARIO_LEVEL_3)
		{
			level = MARIO_LEVEL_2;
			StartUntouchable();
		}
		else if (level == MARIO_LEVEL_2)
		{
			level = MARIO_LEVEL_1;
			StartUntouchable();
		}
		else
			SetState(MARIO_STATE_DIE);
	}
}

void CMario::upLevel()
{
	if (level == MARIO_LEVEL_1)
	{
		dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene())->Pause();
		level = MARIO_LEVEL_2;
	}
	else if (level == MARIO_LEVEL_2)
	{
		dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene())->Pause();
		level = MARIO_LEVEL_3;
	}
}

void CMario::HandleArrowHud()
{
	if (fast)
	{
		if (GetTickCount() - timeAddCountArrow > NUMBER_300)
		{
			timeAddCountArrow = GetTickCount();
			SplusCountArrow();
		}
	}
	else
	{
		if (GetTickCount() - timeAddCountArrow > NUMBER_300)
		{
			timeAddCountArrow = GetTickCount();
			SubCountArrow();
		}
	}
}

void CMario::HandleMarioFly()
{
	
	if (state == MARIO_STATE_FLY)
	{
		DebugOut(L"111 \n");
		vy = -MARIO_GRAVITY_HAVE_STATE_FLY * dt;
		if (y < 10)
		{
			y = 10;
		}
	}
	else if(state == MARIO_STATE_JUMP) {
		DebugOut(L"222 \n");
		vy += 0.002f * dt;
	}
	else if (state == MARIO_STATE_JUMP_HEIGHT) {
		DebugOut(L"333 \n");
		vy += 0.001f * dt;
	}
	else if(state == MARIO_STATE_SLOW_DOWN_SWING_TAIL_FLY && vy > 0){
		vy += 0.00005f * dt;
	}
	else
	{
		if (state == MARIO_STATE_SWING_TAIL)
		{
			DebugOut(L"444 \n");
			vy += MARIO_GRAVITY_SWING_TAIL * dt;
		}
		else
		{
			DebugOut(L"555 \n");
			vy += 0.0018f * dt;
		}
	}
}

void CMario::HandleMarioSwingTail(){
	if(isJump && isActiveWaiSwingTail){
		DebugOut(L" HandleMarioSwingTail \n");
		vy += 0.0000018f * dt;
	}
}

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt);
	DWORD now = GetTickCount();
	HandleArrowHud();
	if (isActiveSwitchScene) vx = MARIO_SPEED_AUTO_SWITCH_SCENE;
	HandleMarioFly();
	if(now - timeKick < MARIO_TIME_KICK && timeKick != 0) {
		SetState(MARIO_STATE_KICK);
	}

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

//	HandleMarioSwingTail();
	DebugOut(L"mario->vy:%f \n",vy);
	coEvents.clear();
	// HandleUpDownLevel();
	if (GetTickCount() - untouchable_start > TIME_MARIO_UNTOUCHABLE)
	{
		untouchable = 0;
		untouchable_start = 0;
	}

	if (state != MARIO_STATE_DIE)
	{
		CalcPotentialCollisions(coObjects, coEvents);
	}
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		float old_vy = vy;
		float old_vx = vx;
		bool isCollisionGold = false;
		bool isCollisionGround = false;
		bool needPushBack = false;
		if (nx != 0)
			vx = 0;
		if (ny < 0)
		{
			vy = 0;
			isJump = false;
		}

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CGoomba *>(e->obj))
			{
				CollisionWithGoomba(e);
				continue;
			}

			if (dynamic_cast<CTurtle *>(e->obj))
			{
				CollisionWithTurtle(e);
				needPushBack = true;
				continue;
			}

			if (dynamic_cast<CHold *>(e->obj))
			{
				isJump = false;
				needPushBack = true;
				HandleHoldCollision(ny, dx, dy, old_vy);
				continue;
			}

			if (dynamic_cast<CPortal *>(e->obj))
			{
				CPortal *p = dynamic_cast<CPortal *>(e->obj);
				CGame::GetInstance()->SwitchScene(p->GetSceneId());
			}

			if (dynamic_cast<CTurtleJump *>(e->obj))
			{
				CTurtleJump *turtleJump = dynamic_cast<CTurtleJump *>(e->obj);
				if (e->ny < 0)
				{
					if (turtleJump->GetState() == TURTLE_JUMP_STATE_FLY)
					{
						turtleJump->SetState(TURTLE_JUMP_STATE_WALKING);
					}
					if (turtleJump->GetState() == TURTLE_JUMP_STATE_WALKING)
					{
						turtleJump->SetState(TURTLE_JUMP_STATE_DIE);
					}
				}
				else if (e->nx != 0)
				{
					// == 0 la co va cham
					if (untouchable == 0)
					{
						if (turtleJump->GetState() == TURTLE_JUMP_STATE_DIE)
						{
							if (e->nx < 0)
							{
								turtleJump->SetState(TURTLE_JUMP_STATE_DIE_MOVING_RIGHT);
							}
							if (e->nx > 0)
							{
								turtleJump->SetState(TURTLE_JUMP_STATE_DIE_MOVING_LEFT);
							}
							timeKick = GetTickCount();
						}
						else if (turtleJump->GetState() == TURTLE_JUMP_STATE_FLY || turtleJump->GetState() == TURTLE_JUMP_STATE_WALKING)
						{
							downLevel();
						}
					}
				}
			}

			else if (dynamic_cast<CFlowSwitchScene *>(e->obj))
			{
				CFlowSwitchScene *flowSwitchScene = dynamic_cast<CFlowSwitchScene *>(e->obj);
				flowSwitchScene->SetState(FLOW_SWITCH_SCENE_STATE_FLY);
				SetState(MARIO_STATE_SWITCH_SCENE);
				isActiveSwitchScene = true;
				timeSwitchScene = GetTickCount();
				// flowSwitchScene->SetStateObjectDelete(NUMBER_1);
			}

			else if (dynamic_cast<CGoombafly *>(e->obj))
			{
				CGoombafly *goombafly = dynamic_cast<CGoombafly *>(e->obj);
				// jump on top >> kill Goomba and deflect a bit
				if (e->ny < 0)
				{
					if (goombafly->GetUntouchableGoombaFly() == Touchable)
					{
						if (goombafly->GetState() == GOOMBA_FLY_STATE_FLY)
						{
							goombafly->SetState(GOOMBA_FLY_STATE_WALKING);
							goombafly->StartUntouchableGoombaFly();
							JumpWhenCollision();
						}
						else
						{
							JumpWhenCollision();
							goombafly->SetState(GOOMBA_FLY_STATE_DIE);
						}
					}
				}
				else if (e->nx != 0)
				{
					if (untouchable == 0)
					{
						if (goombafly->GetState() != GOOMBA_FLY_STATE_DIE)
						{
							if (level > MARIO_LEVEL_1)
							{
								level = MARIO_LEVEL_1;
								StartUntouchable();
							}
							else
								SetState(MARIO_STATE_DIE);
						}
					}
				}
			}

			else if (dynamic_cast<CMoney *>(e->obj))
			{
				CMoney *money = dynamic_cast<CMoney *>(e->obj);
				money->SetStateObjectDelete(NUMBER_1);
				CHud::GetInstance()->AddNumberGold(NUMBER_1);
			}
			else if (dynamic_cast<CMushroom *>(e->obj))
			{
				CollisionWithMushroom(e);
			}
			else if (dynamic_cast<CItemLeaf *>(e->obj))
			{
				CItemLeaf *leaf = dynamic_cast<CItemLeaf *>(e->obj);
				y = y - PLUS_POSITION_Y;
				StartUpDownLevel();
				leaf->SetStateObjectDelete(NUMBER_1); // delete obj left
				upLevel();
				CHud::GetInstance()->AddNumberMoney(NUMBER_1000);
			}
			else if (dynamic_cast<CBrick *>(e->obj))
			{
				needPushBack = true;
				if (e->ny > 0)
				{
					CBrick *brick = dynamic_cast<CBrick *>(e->obj);
					if (brick->GetState() == BRICK_STATE_ANIMATION)
					{
						brick->SetState(BRICK_STATE_DIE);
						int type = brick->GetTypeItemRender();
						renderItemCollisionBrick(type, brick->x, brick->y);
					}
				}
			}
			else if (dynamic_cast<CBrickFloor *>(e->obj))
			{
				isJump = false;
				needPushBack = true;
				isCollisionGround = true;
				SetIsActiveFly(false);
			}
			else if (dynamic_cast<CBrickColliBroken *>(e->obj))
			{
				needPushBack = true;
				bool tempIsCollisionGold = false;
				CollisionWithBrickColliBroken(e, tempIsCollisionGold);
				isCollisionGold = tempIsCollisionGold;
			}
			else if (dynamic_cast<CBullet *>(e->obj))
			{
				downLevel();
			}
			else if (dynamic_cast<CFlower *>(e->obj) || dynamic_cast<CFlowerType2 *>(e->obj))
			{
				downLevel();
			}
		}
		if (isCollisionGold && !isCollisionGround)
		{
			WalkThrough(old_vx, old_vy);
		}

		if (needPushBack)
		{
			x += min_tx * dx + nx * 0.4f;
			y += min_ty * dy + ny * 0.4f;
		}
	}
	if (GetTickCount() - timeSwitchScene > NUMBER_2500 && timeSwitchScene != 0)
	{
		isActiveSwitchScene = false;
		CGame::GetInstance()->SwitchScene(ID_SCENE_4);
		CGame::GetInstance()->SetCamPos(0, 0);
	}
	ClearCollisionEvent(coEvents);

	if (GetTickCount() - second > NUMBER_1000)
	{
		CHud::GetInstance()->SubTime(1);
		second = GetTickCount();
	}
	HandleAttack();
}

void CMario::SetState(int state)
{
	switch (state)
	{
	case MARIO_STATE_WALKING_RIGHT:
		nx = DIRECTION_RIGHT_X;
		// vx = MARIO_WALKING_SPEED_NORMAL;
		vx = 0.12f;
		if (GetState() == MARIO_STATE_FLY) return;
		if (fast) vx = 0.2f; // MARIO_WALKING_SPEED_PAST;
		break;
	case MARIO_STATE_WALKING_LEFT:
		nx = DIRECTION_LEFT_X;
		vx = -0.12f;
		if (GetState() == MARIO_STATE_FLY) return;
		if (fast) vx = -0.2f;
		break;
	case MARIO_STATE_JUMP:
		if (isJump) return;
		// vx = 0.7f;
		// if (nx < 0) vx = -0.7f;
		isJump = true;
		vy = -0.4f;
		break;
	case MARIO_STATE_JUMP_HEIGHT:
		if (isJump) return;
		isJump = true;
		vy = -0.5f;
		// vx = 0.6f;
		// if(nx < 0) vx = -0.6f;
		break;
	case MARIO_STATE_IDLE:
		vx = 0;
		break;
	case MARIO_STATE_SIT_DOWN:
		vx = 0;
		break;
	case MARIO_STATE_ATTACT:
		vx = 0;
		break;
	case MARIO_STATE_DIE:
		vy = -MARIO_DIE_DEFLECT_SPEED;
		break;
	case MARIO_STATE_UP_LEVEL:
		vx = 0;
		break;
	case MARIO_STATE_LEVEL_3_ATTACK_FRAME_1:
		vx = 0;
		break;
	case MARIO_STATE_LEVEL_3_ATTACK_FRAME_2:
		vx = 0;
		break;
	case MARIO_STATE_LEVEL_3_ATTACK_FRAME_3:
		vx = 0;
		break;
	case MARIO_STATE_SWING_TAIL:
		vx = 0;
		break;

	case MARIO_STATE_SWITCH_SCENE:
		vx = NORMAL_SPEED; // NORMAL_SPEED = 0.05f;
		break;
	case MARIO_STATE_KICK:
		vx = 0;
		break;
	}

	CGameObject::SetState(state);
}

void CMario::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + MARIO_BIG_BBOX_WIDTH;
	bottom = y + MARIO_BIG_BBOX_HEIGHT;

	if (level == MARIO_LEVEL_3)
	{
		if (state == MARIO_STATE_SIT_DOWN)
		{
			top = y + NUMBER_12;
		}
		if (nx > 0)
		{
			left = x + NUMBER_8;
			right = x + MARIO_LEVEL3_BBOX_WIDTH;
		}
		//
		// right = x + 20;
	}
	else if (level == MARIO_LEVEL_2)
	{
		if (state == MARIO_STATE_SIT_DOWN)
		{
			top = y + NUMBER_14;
		}
			bottom = y + 25;
	}
	else
	{
		bottom = y + NUMBER_14;
	}
}

void CMario::StartUpDownLevel()
{
	startUpDownLevel = GetTickCount();
}

void CMario::HandleUpDownLevel()
{
	if (GetTickCount() - startUpDownLevel < NUMBER_1500)
	{
		SetState(MARIO_STATE_UP_LEVEL);
	}
	if (GetTickCount() - startUpDownLevel > NUMBER_1500)
	{
		startUpDownLevel = NumberZero;
	}
}

void CMario::Reset()
{
	SetState(MARIO_STATE_IDLE);
	SetPosition(start_x, start_y);
	SetSpeed(0, 0);
}

void CMario::ClearCollisionEvent(vector<LPCOLLISIONEVENT> coEvents)
{
	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];
}

void CMario::HandleHoldCollision(float ny, float dx, float dy, float old_vy)
{
	if (ny > 0)
	{
		y += dy;
		vy = old_vy;
	}
}

void CMario::renderItemCollisionBrick(int type, float x, float y)
{
	CAnimationSets *animation_sets = CAnimationSets::GetInstance();
	CGameObject *obj = NULL;
	// render gold is money
	if (type == BRICK_ITEM_RENDER_MONEY)
	{
		CAnimationSets *animation_sets = CAnimationSets::GetInstance();
		CGameObject *obj = NULL;
		obj = new CMoney(x, y, true);
		obj->SetPosition(x, y);
		LPANIMATION_SET ani_set = animation_sets->Get(OBJECT_TYPE_MONEY);
		obj->SetAnimationSet(ani_set);
		dynamic_cast<CPlayScene *>(CGame::GetInstance()->GetCurrentScene())->AddObject(obj);
		// CHud::GetInstance()->AddNumberGold(NUMBER_1);
	}
	// render number: 100, 1000,...
	else if (type == BRICK_ITEM_RENDER_NUMBER)
	{
		CAnimationSets *animation_sets = CAnimationSets::GetInstance();
		CGameObject *obj = NULL;
		obj = new CNumber(x, y);
		obj->SetPosition(x, y);
		LPANIMATION_SET ani_set = animation_sets->Get(OBJECT_TYPE_NUMBER);
		obj->SetAnimationSet(ani_set);
		dynamic_cast<CPlayScene *>(CGame::GetInstance()->GetCurrentScene())->AddObject(obj);
	}
	else if (type == BRICK_ITEM_RENDER_MUSHROOM)
	{
		CAnimationSets *animation_sets = CAnimationSets::GetInstance();
		CGameObject *obj = NULL;
		obj = new CMushroom();
		obj->SetPosition(x, y - 20);
		LPANIMATION_SET ani_set = animation_sets->Get(OBJECT_TYPE_MUSHROOM);
		obj->SetAnimationSet(ani_set);
		dynamic_cast<CPlayScene *>(CGame::GetInstance()->GetCurrentScene())->AddObject(obj);
	}
	else if (type == BRICK_ITEM_RENDER_LEAF)
	{
		CAnimationSets *animation_sets = CAnimationSets::GetInstance();
		CGameObject *obj = NULL;
		obj = new CItemLeaf(x, y);
		obj->SetPosition(x, y);
		LPANIMATION_SET ani_set = animation_sets->Get(OBJECT_TYPE_LEAF);
		obj->SetAnimationSet(ani_set);
		dynamic_cast<CPlayScene *>(CGame::GetInstance()->GetCurrentScene())->AddObject(obj);
	}
	// type == 5 is item when collision with brickBroken
	else if (type == NUMBER_5)
	{
		obj = new CBrickColliBroken(2);
		obj->SetPosition(x, y);
		LPANIMATION_SET ani_set = animation_sets->Get(153);
		obj->SetAnimationSet(ani_set);
		dynamic_cast<CPlayScene *>(CGame::GetInstance()->GetCurrentScene())->AddObject(obj);
	}
	// type == 6 is 4 item when collision with brickBroken
	else if (type == NUMBER_6)
	{
		for (int i = NUMBER_1; i <= NUMBER_4; i++)
		{
			obj = new CItemFly(i);
			obj->SetPosition(x, y);
			LPANIMATION_SET ani_set = animation_sets->Get(88);
			obj->SetAnimationSet(ani_set);
			dynamic_cast<CPlayScene *>(CGame::GetInstance()->GetCurrentScene())->AddObject(obj);
		}
	}
}

void CMario::SplusCountArrow()
{
	if (countArrow == NUMBER_6)
		return;
	countArrow++;
}

void CMario::SubCountArrow()
{
	if (countArrow == NUMBER_0)
		return;
	countArrow--;
}

void CMario::WalkThrough(float _vx, float _vy)
{
	x += dx;
	y += dy;
	vx = _vx;
	vy = _vy;
}

void CMario::JumpWhenCollision()
{
	vy = -0.3f;
}

void CMario::CollisionWithGoomba(LPCOLLISIONEVENT collisionEvent)
{
	CGoomba *goomba = dynamic_cast<CGoomba *>(collisionEvent->obj);
	if (goomba->GetState() != GOOMBA_STATE_START_DIE_COLLISION_TURTLR)
	{

		if (collisionEvent->ny < 0)
		{
			if (goomba->GetState() != GOOMBA_STATE_DIE)
			{
				goomba->SetTimeStartDie(GetTickCount());
				goomba->SetState(GOOMBA_STATE_DIE);
				JumpWhenCollision();
			}
		}
		else if (collisionEvent->nx != 0)
		{
			if (untouchable == 0)
			{
				if (goomba->GetState() != GOOMBA_STATE_DIE)
				{
					downLevel();
				}
			}
		}
	}
}

void CMario::CollisionWithTurtle(LPCOLLISIONEVENT collisionEven)
{
	CTurtle *turtle = dynamic_cast<CTurtle *>(collisionEven->obj);
	turtle->SetTimeRelive(GetTickCount());
	if (collisionEven->ny < 0)
	{
		if (turtle->GetState() == TURTLE_STATE_DIE_MOVING_RIGHT || turtle->GetState() == TURTLE_STATE_DIE_MOVING_LEFT)
		{
			turtle->SetState(TURTLE_STATE_DIE);
			JumpWhenCollision();
			return;
		}
		if (turtle->GetState() == TURTLE_STATE_DIE)
		{
			float xTurtle, yTurtle;
			turtle->GetPosition(xTurtle, yTurtle);
			if (x < xTurtle)
			{
				turtle->SetState(TURTLE_STATE_DIE_MOVING_RIGHT);
			}
			else
			{
				turtle->SetState(TURTLE_STATE_DIE_MOVING_LEFT);
			}
		}

		if (turtle->GetState() == TURTLE_STATE_WALKING_LEFT || turtle->GetState() == TURTLE_STATE_WALKING_RIGHT)
		{
			turtle->SetState(TURTLE_STATE_DIE);
			JumpWhenCollision();
		}
	}
	else if (collisionEven->nx != 0)
	{
		if (untouchable == 0)
		{
			if (turtle->GetState() == TURTLE_STATE_DIE || turtle->GetState() == TURTLE_STATE_DIE_COLLISION_TAIL)
			{
				if (collisionEven->nx < 0)
				{
					turtle->SetState(TURTLE_STATE_DIE_MOVING_RIGHT);
				}
				if (collisionEven->nx > 0)
				{
					turtle->SetState(TURTLE_STATE_DIE_MOVING_LEFT);
				}
				renderItemCollisionBrick(2, turtle->x, turtle->y);
				
				timeKick = GetTickCount();
			}
			else
			{
				downLevel();
			}
		}
	}
}

void CMario::CollisionWithMushroom(LPCOLLISIONEVENT collisionEven)
{
	CMushroom *mushroom = dynamic_cast<CMushroom *>(collisionEven->obj);
	y = y - PLUS_POSITION_Y;
	StartUpDownLevel();
	mushroom->SetStateObjectDelete(NUMBER_1);
	upLevel();
}

void CMario::CollisionWithBrickColliBroken(LPCOLLISIONEVENT collisionEven, bool &tempIsCollisionGold)
{
	CBrickColliBroken *brickColliBroken = dynamic_cast<CBrickColliBroken *>(collisionEven->obj);
	int typeBrick = brickColliBroken->GetType();
	if (typeBrick == 2)
	{
		if (!brickColliBroken->GetActiveCollisiond())
		{
			float x, y;
			brickColliBroken->GetPosition(x, y);
			brickColliBroken->SetPosition(x, y + 8);
		}
		brickColliBroken->SetActiveCollisiond();
		brickColliBroken->SetState(BRICK_COLLISION_BROKENT_ITEM_AFTER_COLLISON);
	}
	if (brickColliBroken->GetActiveGold() && typeBrick != 3 && typeBrick != 2)
	{
		brickColliBroken->SetStateObjectDelete(NUMBER_1);
		CHud::GetInstance()->AddNumberGold(NUMBER_1);
		// isCollisionGold = true;
		tempIsCollisionGold = true;
	}
	if (collisionEven->ny > 0)
	{
		if (brickColliBroken->GetType() == NUMBER_3)
		{
			float brickX, bricLY;
			brickColliBroken->GetPosition(brickX, bricLY);
			if (brickColliBroken->GetAllowRenderItem())
			{
				renderItemCollisionBrick(5, brickX, bricLY - NUMBER_16);
				brickColliBroken->SetAllowRenderItem();
			}
		}
	}

	if (brickColliBroken->GetActiveCollisiond())
	{
		dynamic_cast<CPlayScene *>(CGame::GetInstance()->GetCurrentScene())->SetChangeBrickCollisionGold();
	}
}

void CMario::Render()
{
	int ani = 0;
	if (state == MARIO_STATE_UP_LEVEL)
	{
		if (level == MARIO_LEVEL_2)
		{
			if (nx > 0)
				ani = MARIO_ANI_LEVEL_1_TO_2_RIGHT;
			else
				ani = MARIO_ANI_LEVEL_1_TO_2_LEFT;
		}
		else if (level == MARIO_LEVEL_3)
		{
			ani = MARIO_ANI_LEVEL_2_TO_3_RIGHT;
		}
	}
	else if (state == MARIO_STATE_JUMP || state == MARIO_STATE_JUMP_HEIGHT)
	{
		switch (level)
		{
		case MARIO_LEVEL_1:
			if (nx > 0)
				ani = MARIO_ANI_LEVEL_1_JUMP_RIGHT;
			else
				ani = MARIO_ANI_LEVEL_1_JUMP_LEFT;
			break;
		case MARIO_LEVEL_2:
			if (nx > 0)
				ani = MARIO_ANI_LEVEL_2_JUMP_RIGHT;
			else
				ani = MARIO_ANI_LEVEL_2_JUMP_LEFT;
			break;
		case MARIO_LEVEL_3:
			if (nx > 0)
				ani = MARIO_ANI_LEVEL_3_JUMP_RIGHT;
			else
				ani = MARIO_ANI_LEVEL_3_JUMP_LEFT;
			break;
		}
	}
	else if (state == MARIO_STATE_IDLE)
	{
		switch (level)
		{
		case MARIO_LEVEL_1:
			// fixed animaion
			if (nx > 0)
				ani = MARIO_ANI_IDLE_RIGHT;
			else
				ani = MARIO_ANI_IDLE_LEFT;
			break;
		case MARIO_LEVEL_2:
			if (vy < 0)
			{
				if (nx > 0)
					ani = MARIO_ANI_LEVEL_2_JUMP_RIGHT;
				else
					ani = MARIO_ANI_LEVEL_2_JUMP_LEFT;
			}
			else
			{
				if (nx > 0)
					ani = MARIO_ANI_LEVEL_2_IDLE_RIGHT;
				else
					ani = MARIO_ANI_LEVEL_2_IDLE_LEFT;
			}
			break;
		case MARIO_LEVEL_3:
			if (vy < 0)
			{
				if (nx > 0)
					ani = MARIO_ANI_LEVEL_3_JUMP_RIGHT;
				else
					ani = MARIO_ANI_LEVEL_3_JUMP_LEFT;
			}
			else
			{
				if (nx > 0)
					ani = MARIO_ANI_LEVEL_3_IDLE_RIGHT;
				else
					ani = MARIO_ANI_LEVEL_3_IDLE_LEFT;
			}
			break;
		}
	}
	else if (state == MARIO_STATE_WALKING_RIGHT)
	{
		switch (level)
		{
		case MARIO_LEVEL_1:
			ani = MARIO_ANI_WALKING_RIGHT;
			break;
		case MARIO_LEVEL_2:
			ani = MARIO_BIG_ANI_WALKING_RIGHT;
			if (vy < 0)
				ani = MARIO_ANI_LEVEL_2_JUMP_RIGHT;
			break;
		case MARIO_LEVEL_3:
			ani = MARIO_BIG_ATTACT_ANI_WALKING_RIGHT;
			if (vy < 0)
				ani = MARIO_ANI_LEVEL_3_JUMP_RIGHT;
			break;
		}
	}
	else if (state == MARIO_STATE_WALKING_LEFT)
	{
		switch (level)
		{
		case MARIO_LEVEL_1:
			ani = MARIO_ANI_WALKING_LEFT;
			break;
		case MARIO_LEVEL_2:
			ani = MARIO_BIG_ANI_WALKING_LEFT;
			if (vy < 0)
				ani = MARIO_ANI_LEVEL_2_JUMP_LEFT;
			break;
		case MARIO_LEVEL_3:
			ani = MARIO_BIG_ATTACT_ANI_WALKING_LEFT;
			if (vy < 0)
				ani = MARIO_ANI_LEVEL_3_JUMP_LEFT;
			break;
		}
	}
	else if (state == MARIO_STATE_SIT_DOWN)
	{
		switch (level)
		{
		case MARIO_LEVEL_1:
			if (nx > 0)
				ani = MARIO_ANI_IDLE_RIGHT;
			else
				ani = MARIO_ANI_IDLE_LEFT;
			break;
		case MARIO_LEVEL_2:
			if (nx > 0)
				ani = MARIO_ANI_LEVEL_2_SIT_DOWN_RIGHT;
			else
				ani = MARIO_ANI_LEVEL_2_SIT_DOWN_LEFT;
			break;
		case MARIO_LEVEL_3:
			if (nx > 0)
				ani = MARIO_ANI_LEVEL_3_SIT_DOWN_RIGHT;
			else
				ani = MARIO_ANI_LEVEL_3_SIT_DOWN_LEFT;
			break;
		}
	}

	else if (state == MARIO_STATE_FLY)
	{
		if (nx > 0)
			ani = MARIO_ANI_FLY_RIGHT;
		else
			ani = MARIO_ANI_FLY_LEFT;
	}
	else if(state == MARIO_STATE_SLOW_DOWN_SWING_TAIL_FLY){
		DebugOut(L"render ani slowdown fly");
		if (nx > 0)
			ani = MARIO_ANI_SLOW_DOWN_SWING_TAIL_FLY_RIGHT;
		else
			ani = MARIO_ANI_SLOW_DOWN_SWING_TAIL_FLY_LEFT;
	}
	else if (state == MARIO_STATE_KICK)
	{
		switch (level)
		{
		case MARIO_LEVEL_1:
			ani = MARIO_ANI_LEVEL_1_KICK_LEFT;
			if (nx > 0)
				ani = MARIO_ANI_LEVEL_1_KICK_RIGHT;
			break;
		case MARIO_LEVEL_2:
			ani = MARIO_ANI_LEVEL_2_KICK_LEFT;
			if (nx > 0)
				ani = MARIO_ANI_LEVEL_2_KICK_RIGHT;
			break;
		case MARIO_LEVEL_3:
			ani = MARIO_ANI_LEVEL_3_KICK_LEFT;
			if (nx > 0)
				ani = MARIO_ANI_LEVEL_3_KICK_RIGHT;
			break;
		}
	}

	if (checkAttact && level == MARIO_LEVEL_3)
	{
		if (nx > 0)
			ani = MARIO_ANI_LEVEL_3_ATTAT_RIGHT;
		else
			ani = MARIO_ANI_LEVEL_3_ATTAT_LEFT;
	}

	if (isActiveSwitchScene)
	{
		switch (level)
		{
		case MARIO_LEVEL_1:
			ani = MARIO_ANI_WALKING_RIGHT;
			break;
		case MARIO_LEVEL_2:
			ani = MARIO_BIG_ANI_WALKING_RIGHT;
			break;
		case MARIO_LEVEL_3:
			ani = MARIO_BIG_ATTACT_ANI_WALKING_RIGHT;
			break;
		}
	}

	int alpha = 255;
	if (untouchable) alpha = 128;
	animation_set->at(ani)->Render(x, y, alpha);
	// RenderBoundingBox();
}
