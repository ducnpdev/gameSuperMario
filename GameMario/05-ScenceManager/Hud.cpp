#include "Hud.h"

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
	DebugOut(L"[INFO] sceneID : %d\n", sceneID);

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
	for (int i = 1; i < 7; i++) {
		int split = number % 10;
		number = number / 10;
		arr.push_back(split);
	}
	return ani;
}

void CHud::Render()
{
	CSprites* p = CSprites::GetInstance();
	LPSPRITE sprite;
	// renderRectangle
	sprite = p->Get(8601);
	sprite->DrawFixed(8, 192);
	// render P
	sprite = p->Get(8606);
	sprite->DrawFixed(116, 198);
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

	// render Muiten 
	for (int i = 0; i < 6; i++) {
		sprite = p->Get(8603);
		sprite->DrawFixed(56 + i * 10, 198);
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
    CGameObject::SetState(state);
}


int CHud::SwitchCase(int i) {
	int ani =0;
	switch (i)
	{
	case 0:
		ani = 0;
		break;
	case 1:
		ani = 1;
		break;
	case 2:
		ani = 2;
		break;
	case 3:
		ani = 3;
		break;
	case 4:
		ani = 4;
		break;
	case 5:
		ani = 5;
		break;
	case 6:
		ani = 6;
		break;
	case 7:
		ani = 7;
		break;
	case 8:
		ani = 8;
		break;
	case 9:
		ani = 9;
		break;
	case 10:
		ani = 10;
		break;
	case 11:
		ani = 11;
		break;
	case 12:
		ani = 12;
		break;
	case 13:
		ani = 13;
		break;
	case 14:
		ani = 14;
		break;
	case 15:
		ani = 15;
		break;
	case 16:
		ani = 16;
		break;
	case 17:
		ani = 17;
		break;
	case 18:
		ani = 18;
		break;
	case 19:
		ani = 19;
		break;
	case 20:
		ani = 20;
		break;
	case 21:
		ani = 21;
		break;
	default:
		ani = 0;
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
