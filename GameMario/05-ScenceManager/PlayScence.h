#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scence.h"
#include "GameObject.h"
#include "Brick.h"
#include "Mario.h"
#include "Goomba.h"
#include "Koopas.h"
#include "MorningStar.h"
#include "Money.h"
#include "Number.h"
#include "BrickFloor.h"
#include "Cloud.h"
#include "Mushroom.h"
#include "Turtle.h"
#include "IntroPlayerSecond.h"
#include "Square.h"
#include "Goombafly.h"
#include "Hold.h"
#include "Tail.h"
#include "Bullet.h"
#include "BrickColliBroken.h"
#include "IntroPlayer.h"
#include "IntroMushroom.h"
#include "IntroStar.h"
#include "TurtleJump.h"
#include "IntroGoomba.h"
#include "IntroTurtleBrack.h"
#include "IntroBackground.h"
#include "IntroBackgroundSuper.h"
#include "MarioWorldMap.h"
#include "Hud.h"
#include <cmath>
#include "IntroPlayerSecond.h"
class CPlayScene: public CScene
{
protected: 
	CMario *player;					// A play scene has to have player, right? 
	CMarioWorldMap *playerWorldMap;
	CHud *hud;
	DWORD pauseStartAt;
	bool isPause = false;
	
	vector<LPGAMEOBJECT> objects;
	void _ParseSection_TILEMAP(string line);
	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_OBJECTS(string line);

	
public: 
	CPlayScene(int id, LPCWSTR filePath, LPCWSTR pathBackground);
				
	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();
	void Pause();
	void UnPause();

	CMario * GetPlayer() { return player; }
	CMarioWorldMap* GetPlayerWorldMap() { return playerWorldMap; }
	CHud* GetHud() { return hud; }

	//friend class CPlayScenceKeyHandler;
	void LoadResourcesTitledMap(int tileMapID);
	void AddObject(LPGAMEOBJECT gameObject);

	vector<LPGAMEOBJECT> GetObjects() { return objects; }
};

class CPlayScenceKeyHandler : public CScenceKeyHandler
{
public: 
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode) {};
	CPlayScenceKeyHandler(CScene *s) :CScenceKeyHandler(s) {};
};

