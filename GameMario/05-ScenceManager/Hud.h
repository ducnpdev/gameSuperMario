#pragma once
#include "GameObject.h"
#include "Define.h"
#include "Utils.h"
#include "Portal.h"
#include "Game.h"
#include "BrickFloor.h"

class CHud : public CGameObject
{
    int typeRender;
    int time;
    int numberGold;
    int numberMoney;
    static CHud * __instance;
public:
    CHud();
    ~CHud();
    // CHud(int type);
    virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
    virtual void SetState(int state);
    void CreateData();
    int ConvertNumberToSprite(int number);
    int SwitchCase(int i);

    void ResetTime();
    void SetTime(int t) { this->time = t; }
    int GetTime();
    void ResetMoney();
    void SetMoney(int m) { this->numberMoney = m; }
    int GetMoney();
    void ResetGold();
    void SetGold(int g) { this->numberGold = g; }
    int GetGold();

    void AddTime(int t) { time += t; };
    void SubTime(int t) { time -= t; }

    void AddNumberMoney(int m) {numberMoney += m;}
    void SubNumberMoney(int m) {numberMoney -= m;}
    
    void AddNumberGold(int g) {numberGold += g;}
    void SubNumberGold(int g) {numberGold -= g;}
    static CHud * GetInstance();
};

