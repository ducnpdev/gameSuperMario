#pragma once
#include "GameObject.h"
#include "Define.h"
#include "Utils.h"

class CBrickColliBroken : public CGameObject
{
    int type;
	bool activeGold = false;
	bool activeCollision = false;
	bool allowRenderItem = true; // true = ok, false is not render; 
	DWORD timeBrickBrokenRelive;
public:
	CBrickColliBroken(int t);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void SetState(int state);
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void SetActiveGold(int _type = true) { activeGold = _type; };
	bool GetActiveGold() { return this->activeGold; };
	void SetActiveCollisiond(int _active = true) { activeCollision = _active; };
	bool GetActiveCollisiond() { return this->activeCollision; };
	int GetType() { return this->type; };

	void SetAllowRenderItem(int _isRender = false) { allowRenderItem = _isRender; };
	bool GetAllowRenderItem() { return this->allowRenderItem; };

	void SetTimeBrickBrokenRelive(DWORD time) { this->timeBrickBrokenRelive = time; }
	DWORD GetTimeBrickBrokenRelive() { return this->timeBrickBrokenRelive; }
};

