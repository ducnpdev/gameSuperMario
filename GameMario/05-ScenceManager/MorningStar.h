#pragma once
#include "GameObject.h"
#include "Define.h"
#include "Utils.h"

class CMorningStar : public CGameObject
{
	int ms_level;
	int untouchable;
	DWORD mstar_untouchable_start;
	bool flag = false;
	bool checkAttact_MS = false;
	int ms_nx = 1;
public:
	void setAttactMS(bool check, int nx);
	CMorningStar() : CGameObject() { ms_level = mstar_level_1; };
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	CAnimation *getCurrentAnimation();
	void resetCurrentFrame();
	void SetState(int state);
	void SetLevel(int l) { ms_level = l; };
	void StartMorningStar() { untouchable = 1; mstar_untouchable_start = GetTickCount(); };
	
	void isColidingObjects(vector<LPGAMEOBJECT>* coObjects, vector<LPGAMEOBJECT>& colidingObjects);
	

	void checktest();
};

