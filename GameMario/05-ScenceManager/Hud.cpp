#include "Hud.h"
#include "Mario.h"
#include "PlayScence.h"


CHud * CHud::__instance = NULL;

CHud * CHud::GetInstance() {
	if (__instance == NULL) __instance = new CHud();
	return __instance;
}

CHud::CHud()
{
	CreateData();
}

void CHud::CreateData()
{
	LPSCENE curentScene = CGame::GetInstance()->GetCurrentScene();
	int sceneID = curentScene->getCurrentID();
	// DebugOut(L"[INFO] sceneID : %d\n", sceneID);

	if (sceneID == NUMBER_4) {
		SetTime(0);
		SetMoney(0);
		SetGold(0);
	}
	if (sceneID == NUMBER_1) {
		SetTime(NUMBER_300);
		SetMoney(NUMBER_0);
		SetGold(NUMBER_0);
	}
	//second = GetTickCount();
}

void CHud::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
    left = x;
	top = y;
	right = x+1;
	bottom = y+1;
}

void CHud::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{	
	// DebugOut(L"Hud time: %d \n", time);
}

int CHud::ConvertNumberToSprite(int number) {
	int ani = 1;
	int money[6];
	std::vector< int > arr;
	for (int i = NUMBER_1; i < NUMBER_7; i++) {
		int split = number % 10;
		number = number / 10;
		arr.push_back(split);
	}
	return ani;
}

void CHud::Render()
{
	CMario* mario = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	//
	CSprites* p = CSprites::GetInstance();
	LPSPRITE sprite;
	// renderRectangle
	sprite = p->Get(8601);
	sprite->DrawFixed(8, 192);
	
	// render M
	sprite = p->Get(8605);
	sprite->DrawFixed(12, 208);
	// render map 
	sprite = p->Get(8611);
	sprite->DrawFixed(45, 200);

	// render all amp 
	sprite = p->Get(8614);
	sprite->DrawFixed(45, 208);

	// render square 
	for (int i = 0; i < 3; i++) {
		sprite = p->Get(8602);
		sprite->DrawFixed(172+ i*24, 192);
	}

	// render Muiten back
	for (int i = 0; i < 6; i++) {
		sprite = p->Get(8604);
		sprite->DrawFixed(56 + i * 10, 198);
	}
	// render Muiten white
	if (mario != NULL) {
		int arrowBack = mario->GetCountArrow();
		if (mario->GetIsActiveFly()) arrowBack = NUMBER_6;
		for (int i = 0; i < arrowBack; i++) {
			sprite = p->Get(8603);
			sprite->DrawFixed(56 + i * 10, 198);
		}
		// render P 
		sprite = p->Get(8607);
		sprite->DrawFixed(116, 198);
		if ((arrowBack == NUMBER_6) && (GetTickCount() - timeRenderPWhite > 500)) {
			sprite = p->Get(8606);
			sprite->DrawFixed(116, 198);
			timeRenderPWhite = GetTickCount();
			mario->SetIsActiveFly();
		}
	}
	else {
		sprite = p->Get(8607);
		sprite->DrawFixed(116, 198);
	}

	int tempTime = time;
	for (int i = 0; i < 3; i++) {
		int split = tempTime % 10;
		tempTime = tempTime / 10;
		int ani = SwitchCase(split);
		sprite = p->Get(8610 + ani);
		sprite->DrawFixed(148 - i * 7, 208);
	}

	int tempGold = numberGold;
	for (int i = 0; i < 2; i++) {
		int split = tempGold % 10;
		tempGold = tempGold / 10;
		int ani = SwitchCase(split);
		sprite = p->Get(8610 + ani);
		sprite->DrawFixed(148 - i * 7, 200);
	}

	int tempMoney = numberMoney;
	for (int i = 0; i < 7; i++) {
		int split = tempMoney % 10;
		tempMoney = tempMoney / 10;
		sprite = p->Get(8610 + split);
		sprite->DrawFixed(106 - i * 8, 208);
	}

	// RenderBoundingBox();
}

void CHud::SetState(int state)
{
	//DebugOut(L"update hub \n");
    CGameObject::SetState(state);
	/*if (GetTickCount() - second > NUMBER_1000)
		{
			SubTime(1);
			second = GetTickCount();
		}*/
}


int CHud::SwitchCase(int i) {
	int ani = NUMBER_0;
	switch (i)
	{
	case NUMBER_0:
		ani = NUMBER_0;
		break;
	case NUMBER_1:
		ani = NUMBER_1;
		break;
	case NUMBER_2:
		ani = NUMBER_2;
		break;
	case NUMBER_3:
		ani = NUMBER_3;
		break;
	case NUMBER_4:
		ani = NUMBER_4;
		break;
	case NUMBER_5:
		ani = NUMBER_5;
		break;
	case NUMBER_6:
		ani = NUMBER_6;
		break;
	case NUMBER_7:
		ani = NUMBER_7;
		break;
	case NUMBER_8:
		ani = NUMBER_8;
		break;
	case NUMBER_9:
		ani = NUMBER_9;
		break;
	case NUMBER_10:
		ani = NUMBER_10;
		break;
	case NUMBER_11:
		ani = NUMBER_11;
		break;
	case NUMBER_12:
		ani = NUMBER_12;
		break;
	case NUMBER_13:
		ani = NUMBER_13;
		break;
	case NUMBER_14:
		ani = NUMBER_14;
		break;
	case NUMBER_15:
		ani = NUMBER_15;
		break;
	case NUMBER_16:
		ani = NUMBER_16;
		break;
	case NUMBER_17:
		ani = NUMBER_17;
		break;
	case NUMBER_18:
		ani = NUMBER_18;
		break;
	case NUMBER_19:
		ani = NUMBER_19;
		break;
	case NUMBER_20:
		ani = NUMBER_20;
		break;
	case NUMBER_21:
		ani = NUMBER_21;
		break;
	default:
		ani = NUMBER_0;
		break;
	}
	return ani;
}

void CHud::ResetTime()
{
	this->time = 0;
}

int CHud::GetTime()
{
	return this->time;
}

void CHud::ResetMoney()
{
	this->numberMoney = 0;
}

int CHud::GetMoney()
{
	return this->numberMoney;
}

void CHud::ResetGold()
{
	this->numberGold = 0;
}

int CHud::GetGold()
{
	return this->numberGold;
}

CHud::~CHud() {
	__instance = NULL;
}
