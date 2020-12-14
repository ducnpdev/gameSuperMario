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
#include "Enemies.h"
//CMorningStar* morningstar;

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
		level = MARIO_LEVEL_2;
	}
	else if (level == MARIO_LEVEL_2)
	{
		level = MARIO_LEVEL_3;
	}
}

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (GetTickCount() - second > NUMBER_1000) {
		CHud::GetInstance()->SubTime(1);
		second = GetTickCount();
	}
	CGameObject::Update(dt);
	if (state == MARIO_STATE_FLY) {
		vy = -0.005f * dt;
		if (y < 10) {
			y = 10;
		}
	}
	else {
		if (state == MARIO_STATE_SWING_TAIL)
		{
			vy += MARIO_GRAVITY_SWING_TAIL * dt;
		}
		else
		{
			vy += MARIO_GRAVITY * dt;
		}
	}
	// Simple fall down
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	HandleUpDownLevel();
	if (GetTickCount() - untouchable_start > TIME_MARIO_UNTOUCHABLE)
	{
		untouchable = 0;
		untouchable_start = 0;
	}
	HandleAttack();
	// turn off collision when die
	if (state != MARIO_STATE_DIE)
	{
		CalcPotentialCollisions(coObjects, coEvents);
	}
	// No collision occured, proceed normally
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
			
			if (dynamic_cast<CTurtleJump*>(e->obj)) {
				CTurtleJump* turtleJump = dynamic_cast<CTurtleJump*>(e->obj);
				if (e->ny < 0)
				{
					if (turtleJump->GetState() == TURTLE_JUMP_STATE_FLY)
					{
						turtleJump->SetState(TURTLE_JUMP_STATE_WALKING);
					}
					if(turtleJump->GetState() == TURTLE_JUMP_STATE_WALKING)
					{
						turtleJump->SetState(TURTLE_JUMP_STATE_DIE);
					}
					
				}
				else if (e->nx != 0)
				{
					// == 0 la co va cham
					if (untouchable == 0) {
						if (turtleJump->GetState() == TURTLE_JUMP_STATE_DIE) {
							if (e->nx < 0) {
								turtleJump->SetState(TURTLE_JUMP_STATE_DIE_MOVING_RIGHT);
							}
							if (e->nx > 0) {
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
							//vy = -MARIO_JUMP_DEFLECT_SPEED;
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
						else if (turtle->GetState() == TURTLE_STATE_WALKING_LEFT || turtle->GetState() == TURTLE_STATE_WALKING_RIGHT)
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
				// renderItemCollisionBrick(BRICK_ITEM_RENDER_NUMBER, mushroom->x, mushroom->y);
				mushroom->SetStateObjectDelete(NUMBER_1);
				upLevel();
				// CHud::GetInstance()->AddNumberMoney(NUMBER_1000);
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
			else if (dynamic_cast<CBullet *>(e->obj))
			{
				downLevel();
			}
			else if(dynamic_cast<CFlower*>(e->obj) || dynamic_cast<CFlowerType2 *>(e->obj)){
				downLevel();
			}
		}
	}
	ClearCollisionEvent(coEvents);
}

void CMario::Render()
{
	int ani = MARIO_BIG_ANI_IDLE_RIGHT;
	if (state == MARIO_STATE_DIE)
	{
		ani = MARIO_ANI_DIE;
	}
	else if (state == MARIO_STATE_LEVEL_1_TO_2)
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
	else if (level == MARIO_LEVEL_1)
	{
		/*if (state == MARIO_STATE_SIT_DOWN) {
			if (nx > 0) ani = MARIO_ANI_SIT_DOWN_RIGHT;
			else ani = MARIO_ANI_SIT_DOWN_LEFT;
		}*/
		if (vy < 0)
		{
			if (nx > 0)
				ani = MARIO_ANI_JUMP_RIGHT;
			else
				ani = MARIO_ANI_JUMP_LEFT;
		}
		else if (vx == 0)
		{
			if (nx > 0)
				ani = MARIO_ANI_IDLE_RIGHT;
			else
				ani = MARIO_ANI_IDLE_LEFT;
		}
		else if (vx > 0)
			ani = MARIO_ANI_WALKING_RIGHT;
		else
			ani = MARIO_ANI_WALKING_LEFT;
	}
	else if (level == MARIO_LEVEL_2)
	{
		if (vy < 0)
		{
			if (nx > 0)
				ani = MARIO_BIG_ANI_JUMP_RIGHT;
			else
				ani = MARIO_BIG_ANI_JUMP_LEFT;
		}
		else if (vx == 0)
		{
			if (nx > 0)
			{
				if (state == MARIO_STATE_SIT_DOWN)
				{
					ani = MARIO_BIG_ANI_SIT_DOWN_RIGHT;
				}
				else if (state == MARIO_STATE_IDLE)
				{
					ani = MARIO_BIG_ANI_IDLE_RIGHT;
				}
				/*else if(state == ) {

				}*/
			}
			else
			{
				if (state == MARIO_STATE_SIT_DOWN)
				{
					ani = MARIO_BIG_ANI_SIT_DOWN_LEFT;
				}
				else if (state == MARIO_STATE_IDLE)
				{
					ani = MARIO_BIG_ANI_IDLE_LEFT;
				}
			}
			/* if (nx > 0) ani = MARIO_BIG_ANI_IDLE_RIGHT;
			else ani = MARIO_BIG_ANI_IDLE_LEFT;*/
		}
		else if (vx > 0)
			ani = MARIO_BIG_ANI_WALKING_RIGHT;
		else
			ani = MARIO_BIG_ANI_WALKING_LEFT;
	}
	else if (level == MARIO_LEVEL_3)
	{
		if (state == MARIO_STATE_FLY) {

			if (nx > 0)
				ani = MARIO_ANI_FLY_RIGHT;
			else
				ani = MARIO_ANI_FLY_LEFT;
		}
		else if (vy < 0)
		{
			if (nx > 0)
				ani = MARIO_BIG_ATTACT_ANI_JUMP_RIGHT;
			else
				ani = MARIO_BIG_ATTACT_ANI_JUMP_LEFT;
		}
		else if (vx == 0)
		{
			if (nx > 0)
			{
				if (state == MARIO_STATE_SIT_DOWN)
				{
					ani = MARIO_BIG_ATTACT_ANI_SIT_DOWN_RIGHT;
				}
				else if (state == MARIO_STATE_IDLE)
				{
					ani = MARIO_BIG_ATTACT_ANI_IDLE_RIGHT;
				}
				else if (state == MARIO_STATE_SWING_TAIL)
				{
					ani = MARIO_ANI_SWING_TAIL_RIGHT;
				}
			}
			else
			{
				if (state == MARIO_STATE_SIT_DOWN)
				{
					ani = MARIO_BIG_ATTACT_ANI_SIT_DOWN_LEFT;
				}
				else if (state == MARIO_STATE_IDLE)
				{
					ani = MARIO_BIG_ATTACT_ANI_IDLE_LEFT;
				}
				else if (state == MARIO_STATE_SWING_TAIL)
				{
					ani = MARIO_ANI_SWING_TAIL_LEFT;
				}
			}
		}
		else if (vx > 0)
			ani = MARIO_BIG_ATTACT_ANI_WALKING_RIGHT;
		else
			ani = MARIO_BIG_ATTACT_ANI_WALKING_LEFT;
	}
	if (checkAttact && level == MARIO_LEVEL_3)
	{
		if (nx > 0)
			ani = MARIO_ANI_LEVEL_3_ATTAT_RIGHT;
		else
			ani = MARIO_ANI_LEVEL_3_ATTAT_LEFT;
	}

	int alpha = 255;
	if (untouchable)
		alpha = 128;
	animation_set->at(ani)->Render(x, y, alpha);
	// RenderBoundingBox();
}

void CMario::SetState(int state)
{
	switch (state)
	{
	case MARIO_STATE_WALKING_RIGHT:
		vx = MARIO_WALKING_SPEED_NORMAL;
		if (fast)
		{
			vx = MARIO_WALKING_SPEED_PAST;
		}
		nx = DIRECTION_RIGHT_X;
		break;
	case MARIO_STATE_WALKING_LEFT:
		vx = -MARIO_WALKING_SPEED_NORMAL;
		if (fast)
		{
			vx = -MARIO_WALKING_SPEED_PAST;
		}
		nx = DIRECTION_LEFT_X;
		break;
	case MARIO_STATE_JUMP:
		if (isJump)
		{
			return;
		}
		isJump = true;
		vy = -MARIO_JUMP_SPEED_Y;
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
	case MARIO_STATE_LEVEL_1_TO_2:
		vx = 0;
		break;
		//
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
		//vy = -MARIO_JUMP_SPEED_Y_SWING_TAIL;
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
			top = y + Modify_BBOX;
		}
		right = x + MARIO_LEVEL3_BBOX_WIDTH;
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
	if (GetTickCount() - startUpDownLevel < TIME_MARIO_UP_DOWN_LEVEL)
	{
		SetState(MARIO_STATE_LEVEL_1_TO_2);
	}
	if (GetTickCount() - startUpDownLevel > TIME_MARIO_UP_DOWN_LEVEL)
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
		// CHud::GetInstance()->AddNumberMoney(NUMBER_100);
	}
	else if (type == BRICK_ITEM_RENDER_MUSHROOM)
	{
		CAnimationSets *animation_sets = CAnimationSets::GetInstance();
		CGameObject *obj = NULL;
		obj = new CMushroom();
		obj->SetPosition(x, y-20);
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

