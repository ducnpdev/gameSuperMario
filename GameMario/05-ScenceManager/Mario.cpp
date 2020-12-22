#include <algorithm>
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
	level = MARIO_LEVEL_1;
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
		//		dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene())->Pause();
		level = MARIO_LEVEL_2;
	}
	else if (level == MARIO_LEVEL_2)
	{
		// dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene())->Pause();
		level = MARIO_LEVEL_3;
	}
}

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (isActiveSwitchScene)
	{
		vx = MARIO_SPEED_AUTO_SWITCH_SCENE;
	/*	if (GetTickCount() - timeSwitchScene > NUMBER_2500)
		{
			isActiveSwitchScene = false;
			CGame::GetInstance()->SwitchScene(2);
		}*/
	}

	if (level == MARIO_LEVEL_3 && x > 2353 && vx > 0.000f)
	{
		if (GetTickCount() - timeAddCountArrow > NUMBER_600)
		{
			timeAddCountArrow = GetTickCount();
			SplusCountArrow();
		}
	}
	else
	{
		if (GetTickCount() - timeAddCountArrow > NUMBER_500)
		{
			timeAddCountArrow = GetTickCount();
			SubCountArrow();
		}
	}
	//if(x <= 2360) SubCountArrow();

	if (GetTickCount() - second > NUMBER_1000)
	{
		CHud::GetInstance()->SubTime(1);
		second = GetTickCount();
	}
	CGameObject::Update(dt);

	if (state == MARIO_STATE_FLY)
	{
		vy = -MARIO_GRAVITY_HAVE_STATE_FLY * dt;
		if (y < 10)
		{
			y = 10;
		}
	}
	else
	{
		if (state == MARIO_STATE_SWING_TAIL)
		{
			vy += MARIO_GRAVITY_SWING_TAIL * dt;
		}
		else
		{
			// vy += MARIO_GRAVITY * dt;
			vy += 0.0009f * dt;
		}
	}
	// Simple fall down
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	// HandleUpDownLevel();
	if (GetTickCount() - untouchable_start > TIME_MARIO_UNTOUCHABLE)
	{
		untouchable = 0;
		untouchable_start = 0;
	}
	HandleAttack();
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

		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;
		//
		// Collision logic with other objects
		//
		float old_vy = vy;
		float old_vx = vx;
		// DebugOut(L"continue 123: %f %f \n", old_vx, old_vy);
		if (nx != 0)
		{
			vx = 0;
		}
		if (ny < 0)
		{
			vy = 0;
			isJump = false;
			if (state == MARIO_STATE_SWING_TAIL)
			{
				SetState(MARIO_STATE_IDLE);
			}
		}
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

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
						}
						else if (turtleJump->GetState() == TURTLE_JUMP_STATE_FLY || turtleJump->GetState() == TURTLE_JUMP_STATE_WALKING)
						{
							downLevel();
						}
					}
				}
			}
			else if (dynamic_cast<CHold *>(e->obj))
			{
				HandleHoldCollision(ny, dx, dy, old_vy);
				continue;
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
						}
						else
						{
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
			else if (dynamic_cast<CTurtle *>(e->obj))
			{
				CTurtle *turtle = dynamic_cast<CTurtle *>(e->obj);

				if (e->ny < 0)
				{
					if (turtle->GetState() == TURTLE_STATE_WALKING_LEFT || turtle->GetState() == TURTLE_STATE_WALKING_RIGHT)
					{
						turtle->SetState(TURTLE_STATE_DIE);
						vy = -MARIO_JUMP_DEFLECT_SPEED;
						int type = turtle->GetTypeItemRender();
						renderItemCollisionBrick(type, turtle->x, turtle->y);
					}
				}
				else if (e->nx != 0)
				{
					if (untouchable == 0)
					{
						if (turtle->GetState() == TURTLE_STATE_DIE)
						{
							if (e->nx < 0)
							{
								turtle->SetState(TURTLE_STATE_DIE_MOVING_RIGHT);
							}
							if (e->nx > 0)
							{
								turtle->SetState(TURTLE_STATE_DIE_MOVING_LEFT);
							}
							renderItemCollisionBrick(2, turtle->x, turtle->y);
						}
						// else if (turtle->GetState() == TURTLE_STATE_WALKING_LEFT || turtle->GetState() == TURTLE_STATE_WALKING_RIGHT)
						else
						{
							downLevel();
						}
					}
				}
			}
			else if (dynamic_cast<CGoomba *>(e->obj)) // if e->obj is Goomba
			{
				CGoomba *goomba = dynamic_cast<CGoomba *>(e->obj);
				if (e->ny < 0)
				{
					if (goomba->GetState() != GOOMBA_STATE_DIE)
					{
						goomba->SetTimeStartDie(GetTickCount());
						goomba->SetState(GOOMBA_STATE_DIE);
					}
				}
				else if (e->nx != 0)
				{
					if (untouchable == 0)
					{
						if (goomba->GetState() != GOOMBA_STATE_DIE)
						{
							downLevel();
						}
					}
				}
			} // if Goomba
			else if (dynamic_cast<CPortal *>(e->obj))
			{
				CPortal *p = dynamic_cast<CPortal *>(e->obj);
				CGame::GetInstance()->SwitchScene(p->GetSceneId());
			}
			else if (dynamic_cast<CMoney *>(e->obj))
			{
				CMoney *money = dynamic_cast<CMoney *>(e->obj);
				money->SetStateObjectDelete(NUMBER_1);
				CHud::GetInstance()->AddNumberGold(NUMBER_1);
			}
			else if (dynamic_cast<CMushroom *>(e->obj))
			{
				CMushroom *mushroom = dynamic_cast<CMushroom *>(e->obj);
				y = y - PLUS_POSITION_Y;
				StartUpDownLevel();
				mushroom->SetStateObjectDelete(NUMBER_1);
				upLevel();
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
				SetIsActiveFly(false);
			}
			else if (dynamic_cast<CBrickColliBroken *>(e->obj))
			{
				CBrickColliBroken *brickColliBroken = dynamic_cast<CBrickColliBroken *>(e->obj);
				if (brickColliBroken->GetActiveGold())
				{
					brickColliBroken->SetStateObjectDelete(NUMBER_1);
					CHud::GetInstance()->AddNumberGold(NUMBER_1);
				}
				if (e->ny > 0)
				{
					if (brickColliBroken->GetType() == NUMBER_3)
					{
						float brickX, bricLY;
						brickColliBroken->GetPosition(brickX, bricLY);
						brickColliBroken->SetPosition(brickX, bricLY - 16);
						brickColliBroken->SetActiveCollisiond();
					}
				}
				else
				{
					if (brickColliBroken->GetType() == NUMBER_3 && brickColliBroken->GetActiveCollisiond())
					{
						dynamic_cast<CPlayScene *>(CGame::GetInstance()->GetCurrentScene())->SetChangeBrickCollisionGold();
					}
				}
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
	}
	if (GetTickCount() - timeSwitchScene > NUMBER_2500 && timeSwitchScene != 0)
	{
		isActiveSwitchScene = false;
		CGame::GetInstance()->SwitchScene(NUMBER_4);
	}
	ClearCollisionEvent(coEvents);
}

void CMario::SetState(int state)
{
	switch (state)	
	{
	case MARIO_STATE_WALKING_RIGHT:
		nx = DIRECTION_RIGHT_X;
		vx = MARIO_WALKING_SPEED_NORMAL;
		if (GetState() == MARIO_STATE_FLY)
			return;
		if (fast)
		{
			vx = MARIO_WALKING_SPEED_PAST;
		}
		break;
	case MARIO_STATE_WALKING_LEFT:

		nx = DIRECTION_LEFT_X;
		vx = -MARIO_WALKING_SPEED_NORMAL;
		if (GetState() == MARIO_STATE_FLY)
			return;
		if (fast)
		{
			vx = -MARIO_WALKING_SPEED_PAST;
		}
		break;
	case MARIO_STATE_JUMP:
		if (isJump)
			return;
		isJump = true;
		// vy = -MARIO_JUMP_SPEED_Y;
		vy = -0.3f;

		break;
	case MARIO_STATE_JUMP_HEIGHT:
		if (isJump)
			return;
		isJump = true;
		vy = -0.4f;
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
		vx = 0.05f;
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
			top = y + Modify_BBOX;
		}
		// right = x + MARIO_LEVEL3_BBOX_WIDTH;
	}
	else if (level == MARIO_LEVEL_2)
	{
		if (state == MARIO_STATE_SIT_DOWN)
		{
			top = y + Modify_BBOX;
		}
	}
	else
	{
		bottom = y + MARIO_SMALL_BBOX_HEIGHT;
	}
}

void CMario::StartUpDownLevel()
{
	startUpDownLevel = GetTickCount();
}

void CMario::HandleUpDownLevel()
{
	if (GetTickCount() - startUpDownLevel < 1500)
	{
		SetState(MARIO_STATE_UP_LEVEL);
	}
	if (GetTickCount() - startUpDownLevel > 1500)
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
			// if (vy < 0)
			// 	ani = MARIO_ANI_LEVEL_2_JUMP_RIGHT;
			break;
		case MARIO_LEVEL_3:
			ani = MARIO_BIG_ATTACT_ANI_WALKING_RIGHT;
			// if (vy < 0)
			// 	ani = MARIO_ANI_LEVEL_3_JUMP_RIGHT;
			break;
		}
	}

	int alpha = 255;
	if (untouchable)
		alpha = 128;

	animation_set->at(ani)->Render(x, y, alpha);
	// RenderBoundingBox();
}
