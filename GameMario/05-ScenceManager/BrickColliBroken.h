#pragma once
#include "GameObject.h"
#include "Define.h"
#include "Utils.h"

class CBrickColliBroken : public CGameObject
{
    int type;
	bool activeGold = false;
	bool activeCollision = false;

public:
	CBrickColliBroken(int t);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void SetState(int state);
	void SetActiveGold(int _type = true) { activeGold = _type; };
	bool GetActiveGold() { return this->activeGold; };
	void SetActiveCollisiond(int _active = true) { activeCollision = _active; };
	bool GetActiveCollisiond() { return this->activeCollision; };
	int GetType() { return this->type; };

};

