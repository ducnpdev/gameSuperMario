#include <iostream>
#include <fstream>
#include "ItemLeaf.h"
#include "PlayScence.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"
#include "Define.h"
#include "Background.h"
#include "Flower.h"
#include "IntroPlayer.h"
#include "IntroNumberThree.h"
#include "FlowerType2.h"
#include "IntroLeaf.h"
#include "IntroTurtle.h"
#include "IntroTurtleAni.h"
#include "IntroDoor.h"
#include "IntroGoomba.h"
#include "WorldMapAni.h"

using namespace std;

CBackground *background;

CPlayScene::CPlayScene(int id, LPCWSTR filePath, LPCWSTR pathBackground) : CScene(id, filePath, pathBackground)
{
	key_handler = new CPlayScenceKeyHandler(this);
}

/*
	Load scene resources from scene file (textures, sprites, animations and objects)
	See scene1.txt, scene2.txt for detail format specification
*/

void CPlayScene::_ParseSection_TILEMAP(string line)
{
	vector<string> tokens = split(line);
	if (tokens.size() < 1) return;
	int tileMapID = atoi(tokens[0].c_str());
	LoadResourcesTitledMap(tileMapID);
}

void CPlayScene::_ParseSection_TEXTURES(string line)
{
	vector<string> tokens = split(line);
	if (tokens.size() < 5)
		return; // skip invalid lines
	int texID = atoi(tokens[0].c_str());
	wstring path = ToWSTR(tokens[1]);
	int R = atoi(tokens[2].c_str());
	int G = atoi(tokens[3].c_str());
	int B = atoi(tokens[4].c_str());
	CTextures::GetInstance()->Add(texID, path.c_str(), D3DCOLOR_XRGB(R, G, B));
}

void CPlayScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6)
		return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPDIRECT3DTEXTURE9 tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return;
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}

void CPlayScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3)
		return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2) // why i+=2 ?  sprite_id | frame_time
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i + 1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

void CPlayScene::_ParseSection_ANIMATION_SETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2)
		return; // skip invalid lines - an animation set must at least id and one animation id

	int ani_set_id = atoi(tokens[0].c_str());

	LPANIMATION_SET s = new CAnimationSet();

	CAnimations *animations = CAnimations::GetInstance();

	for (int i = 1; i < tokens.size(); i++)
	{
		int ani_id = atoi(tokens[i].c_str());

		LPANIMATION ani = animations->Get(ani_id);
		s->push_back(ani);
	}

	CAnimationSets::GetInstance()->Add(ani_set_id, s);
}
/*
	Parse a line in section [OBJECTS] 
*/
void CPlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3)
		return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	float x = atof(tokens[1].c_str());
	float y = atof(tokens[2].c_str());

	int ani_set_id = atoi(tokens[3].c_str());

	CAnimationSets *animation_sets = CAnimationSets::GetInstance();

	CGameObject *obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_MARIO:
		if (player != NULL)
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}
		obj = new CMario(x, y);
		player = (CMario *)obj;
		break;
	case OBJECT_TYPE_GOOMBA:
	{
		obj = new CGoomba();
		break;
	}
	case OBJECT_TYPE_HOLD:
	{
		int width = atof(tokens[4].c_str());
		int height = atof(tokens[5].c_str());
		obj = new CHold(width,height);
		break;
	}
	case OBJECT_TYPE_GOOMBA_FLY:
	{
		obj = new CGoombafly(x, y);
		break;
	}
	case OBJECT_TYPE_BRICK:
	{
		CBrick *brick = new CBrick();
		float typeRender = atof(tokens[4].c_str());
		brick->SetTypeItemRender(typeRender);
		obj = brick;
		break;
	}

	case OBJECT_TYPE_TURTLE:
	{
		float typeRender = atof(tokens[4].c_str());
		obj = new CTurtle(typeRender);
		break;
	}
	case OBJECT_TYPE_TURTLE_JUMP:
	{
		obj = new CTurtleJump();
		break;
	}
	case OBJECT_TYPE_BRICK_FLOOR:
	{
		int width = atof(tokens[4].c_str());
		int height = atof(tokens[5].c_str());
		obj = new CBrickFloor(width,height);
		break;
	}
	case OBJECT_TYPE_FLOWER_COLLISION_BROKENT:
	{
		int type = atof(tokens[4].c_str());
		obj = new CBrickColliBroken(type);
		break;
	}
	
	case OBJECT_TYPE_MONEY:
	{
		obj = new CMoney(1.0, 1.0, false);
		break;
	}
	case OBJECT_TYPE_FLOWER:
	{
		int type = atof(tokens[4].c_str());
		obj = new CFlower(x, y,type);
		break;
	}
	case OBJECT_TYPE_FLOWER_TYPE2:
	{
		obj = new CFlowerType2(x, y);	
		break;
	}
	// start intro
	case OBJECT_TYPE_INTRO_PLAYER:
	{
		obj = new CIntroPlayer(x, y);
		break;
	}
	case OBJECT_TYPE_INTRO_PLAYER_SECOND:
	{
		obj = new CIntroPlayerSecond(x, y);
		break;
	}
	case OBJECT_TYPE_INTRO_NUMBER_THREE:
	{
		obj = new CIntroNumberThree(x, y);
		break;
	}
	case OBJECT_TYPE_INTRO_LEAF:
	{
		obj = new CIntroLeaf(x, y);
		break;
	}
	case OBJECT_TYPE_INTRO_TURTLE:
	{
		obj = new CIntroTurtle(x, y);
		break;
	}
	case OBJECT_TYPE_INTRO_DOOR:
	{
		obj = new CIntroDoor(x, y);
		break;
	}
	case OBJECT_TYPE_INTRO_MUSHROOM:
	{
		obj = new CIntroMushroom(x, y);
		break;
	}
	case OBJECT_TYPE_INTRO_STAR:
	{
		obj = new CIntroStar(x, y);
		break;
	}
	case OBJECT_TYPE_INTRO_GOOMBA:
	{
		obj = new CIntroGoomba(x, y);
		break;
	}
	case OBJECT_TYPE_INTRO_TURTLE_BLACK:
	{
		obj = new CIntroTurtleBrack(x, y);
		break;
	}
	case OBJECT_TYPE_INTRO_TURTLE_ANIMATION:
	{
		int veloccity = atof(tokens[4].c_str());
		obj = new CIntroTurtleAni(x, y, veloccity);
		break;
	}
	case OBJECT_TYPE_INTRO_BACKGROUND:
	{
		obj = new CIntroBackground();
		break;
	}
	case OBJECT_TYPE_INTRO_BACKGROUND_SUPER:
	{
		int type = atof(tokens[4].c_str());
		int BreakPosY = atof(tokens[5].c_str());
		obj = new CIntroBackgroundSuper(type, BreakPosY);
		break;
	}

	// end intro
	// start world map
	case OBJECT_TYPE_WORLD_MAP_ANIMATION:
	{
		int type = atof(tokens[4].c_str());
		obj = new CWorldMapAni(type);
		break;
	}
	case OBJECT_TYPE_WORLD_MAP_MARIO_PLAYER:
	{
		if (playerWorldMap != NULL)
		{
			DebugOut(L"[ERROR] MARIO WORLD MAP object was created before!\n");
			// return;
		}
		obj = new CMarioWorldMap();
		playerWorldMap = (CMarioWorldMap*)obj;
		break;
	}
	// end world map
	// start HUD
	case OBJECT_TYPE_HUD:
	{
		obj = CHud::GetInstance();
		break;
	}
	// end HUD
	case OBJECT_TYPE_END_MAP_SWITCH_SCENE:
	{
		obj = new CFlowSwitchScene();
		break;
	}
	case OBJECT_TYPE_PORTAL:
	{
		float r = atof(tokens[4].c_str());
		float b = atof(tokens[5].c_str());
		int scene_id = atoi(tokens[6].c_str());
		obj = new CPortal(x, y, r, b, scene_id);
		break;
	}
	default:
		DebugOut(L"[ERR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	obj->SetPosition(x, y);

	LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);

	obj->SetAnimationSet(ani_set);
	objects.push_back(obj);
}

void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene resources from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);
	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#')
			continue; // skip comment lines

		if (line == "[TILEMAP]")
		{
			section = SCENE_SECTION_TILEMAP;
			continue;
		}
		if (line == "[TEXTURES]")
		{
			section = SCENE_SECTION_TEXTURES;
			continue;
		}
		if (line == "[SPRITES]")
		{
			section = SCENE_SECTION_SPRITES;
			continue;
		}
		if (line == "[ANIMATIONS]")
		{
			section = SCENE_SECTION_ANIMATIONS;
			continue;
		}
		if (line == "[ANIMATION_SETS]")
		{
			section = SCENE_SECTION_ANIMATION_SETS;
			continue;
		}
		if (line == "[OBJECTS]")
		{
			section = SCENE_SECTION_OBJECTS;
			continue;
		}
		if (line[0] == '[')
		{
			section = SCENE_SECTION_UNKNOWN;
			continue;
		}

		//
		// data section
		//
		switch (section)
		{
		case SCENE_SECTION_TEXTURES:
			_ParseSection_TEXTURES(line);
			break;
		case SCENE_SECTION_SPRITES:
			_ParseSection_SPRITES(line);
			break;
		case SCENE_SECTION_ANIMATIONS:
			_ParseSection_ANIMATIONS(line);
			break;
		case SCENE_SECTION_ANIMATION_SETS:
			_ParseSection_ANIMATION_SETS(line);
			break;
		case SCENE_SECTION_OBJECTS:
			_ParseSection_OBJECTS(line);
			break;
		case SCENE_SECTION_TILEMAP:
			_ParseSection_TILEMAP(line);
			break;
		}
	}

	f.close();

	CTextures::GetInstance()->Add(ID_TEX_BBOX, L"textures\\enemies.png", D3DCOLOR_XRGB(255, 255, 255));
}

void CPlayScene::Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way

	// check if game if game is pausing
	// and if it need to be unpause
	UnPause();
	vector<LPGAMEOBJECT> brickCoObjects;
	vector<LPGAMEOBJECT> brickFloorCoObjects;
	vector<LPGAMEOBJECT> brickColliBrokenCoObjects;
	vector<LPGAMEOBJECT> turtleJumpCoObjects;
	vector<LPGAMEOBJECT> enemiesCoObjects;
	vector<LPGAMEOBJECT> otherCoObjects;
	vector<LPGAMEOBJECT> goombaCoObjects;
	vector<LPGAMEOBJECT> holdCoObjects;
	vector<LPGAMEOBJECT> portalCoObjects;
	vector<LPGAMEOBJECT> flowSwitchSceneCoObjects;
	// intro
	vector<LPGAMEOBJECT> playerCoObjects;
	vector<LPGAMEOBJECT> playerSecondCoObjects;
	vector<LPGAMEOBJECT> introTurtleCoObjects;
	vector<LPGAMEOBJECT> introTurtleBlackCoObjects;
	vector<LPGAMEOBJECT> introLeafCoObjects;
	vector<LPGAMEOBJECT> introGoombaCoObjects;
	//
	vector<LPGAMEOBJECT> coObjects;

	for (size_t i = 0; i < objects.size(); i++)
	{
		// start intro
		if (dynamic_cast<CIntroGoomba*>(objects[i])) {
			introGoombaCoObjects.push_back(objects[i]);
			continue;
		}
		if (dynamic_cast<CIntroTurtle*>(objects[i])) {
			introTurtleCoObjects.push_back(objects[i]);
			continue;
		}
		if (dynamic_cast<CIntroTurtleBrack*>(objects[i])) {
			introTurtleBlackCoObjects.push_back(objects[i]);
			continue;
		}
		if (dynamic_cast<CIntroPlayerSecond*>(objects[i]))
		{
			playerSecondCoObjects.push_back(objects[i]);
			continue;
		}
		if (dynamic_cast<CIntroLeaf*>(objects[i]))
		{
			introLeafCoObjects.push_back(objects[i]);
			continue;
		}
		if (dynamic_cast<CFlowSwitchScene*>(objects[i]))
		{
			flowSwitchSceneCoObjects.push_back(objects[i]);
			continue;
		}
		// end intro
		if (dynamic_cast<CTurtleJump*>(objects[i]))
		{
			turtleJumpCoObjects.push_back(objects[i]);
			continue;
		}
		if (dynamic_cast<CBrickColliBroken*>(objects[i]))
		{
			if (isChangeBrickCollisionGold) {
				CBrickColliBroken* abc = dynamic_cast<CBrickColliBroken*>(objects[i]);
				abc->SetActiveGold();
			}
			brickColliBrokenCoObjects.push_back(objects[i]);
			continue;
		}
		if (dynamic_cast<CBrick *>(objects[i]))
		{
			brickCoObjects.push_back(objects[i]);
			continue;
		}
		if (dynamic_cast<CHold *>(objects[i]))
		{
			holdCoObjects.push_back(objects[i]);
			continue;
		}
		if (dynamic_cast<CBrickFloor *>(objects[i]))
		{
			brickFloorCoObjects.push_back(objects[i]);
			continue;
		}
		if (dynamic_cast<CPortal*>(objects[i]))
		{
			portalCoObjects.push_back(objects[i]);
			continue;
		}
		if ( dynamic_cast<CMushroom *>(objects[i]) || dynamic_cast<CTurtle *>(objects[i]) || dynamic_cast<CGoomba *>(objects[i]) || dynamic_cast<CGoombafly *>(objects[i]) || dynamic_cast<CBullet *>(objects[i]) || dynamic_cast<CItemLeaf *>(objects[i]) || dynamic_cast<CMoney *>(objects[i]) || dynamic_cast<CFlower *>(objects[i]))
		{
			enemiesCoObjects.push_back(objects[i]);
			continue;
		}
		otherCoObjects.push_back(objects[i]);
	}

	// if pausing we only update player
	if (isPause)
	{
		player->Update(dt, &coObjects);
	}
	else
	{
		for (size_t i = 0; i < objects.size(); i++)
		{
			/*if (player != NULL) {

			float a  = abs( objects[i]->x - player->x);
			if (a > NUMBER_250) continue;

			}*/
			if (objects[i]->tailDeleteObj)
			{
				objects[i]->deleteObject(objects, i);
			}
			if (objects[i]->objDelete == 1)
			{
				objects[i]->deleteObject(objects, i);
				continue;
			}
			// intro
			if ( dynamic_cast<CIntroPlayer*>(objects[i]) )
			{
				vector<LPGAMEOBJECT> introPlayerCoObjects;
				introPlayerCoObjects.insert(introPlayerCoObjects.begin(), brickFloorCoObjects.begin(), brickFloorCoObjects.end());
				introPlayerCoObjects.insert(introPlayerCoObjects.begin(), playerSecondCoObjects.begin(), playerSecondCoObjects.end());
				objects[i]->Update(dt, &introPlayerCoObjects);
				continue;
			}
			if (dynamic_cast<CIntroPlayerSecond*>(objects[i])) {
				vector<LPGAMEOBJECT> introPlayerSecondCoObjects;
				introPlayerSecondCoObjects.insert(introPlayerSecondCoObjects.begin(), brickFloorCoObjects.begin(), brickFloorCoObjects.end());
				introPlayerSecondCoObjects.insert(introPlayerSecondCoObjects.begin(), introTurtleCoObjects.begin(), introTurtleCoObjects.end());
				introPlayerSecondCoObjects.insert(introPlayerSecondCoObjects.begin(), introLeafCoObjects.begin(), introLeafCoObjects.end());
				introPlayerSecondCoObjects.insert(introPlayerSecondCoObjects.begin(), introGoombaCoObjects.begin(), introGoombaCoObjects.end());
				objects[i]->Update(dt, &introPlayerSecondCoObjects);
				continue;
			}

			if (dynamic_cast<CIntroTurtle*>(objects[i])) {
				vector<LPGAMEOBJECT> introIntroTurtleCoObjects;
				introIntroTurtleCoObjects.insert(introIntroTurtleCoObjects.begin(), playerSecondCoObjects.begin(), playerSecondCoObjects.end());
				introIntroTurtleCoObjects.insert(introIntroTurtleCoObjects.begin(), brickFloorCoObjects.begin(), brickFloorCoObjects.end());
				introIntroTurtleCoObjects.insert(introIntroTurtleCoObjects.begin(), introTurtleBlackCoObjects.begin(), introTurtleBlackCoObjects.end());
				objects[i]->Update(dt, &introIntroTurtleCoObjects);
				continue;
			}
			if (dynamic_cast<CIntroStar*>(objects[i])) {
				objects[i]->Update(dt, &brickFloorCoObjects);
				continue;
			}
			if (dynamic_cast<CIntroMushroom*>(objects[i])) {
				objects[i]->Update(dt, &brickFloorCoObjects);
				continue;
			}
			if (dynamic_cast<CIntroGoomba*>(objects[i])) {
				objects[i]->Update(dt, &brickFloorCoObjects);
				continue;
			}
			if (dynamic_cast<CIntroNumberThree*>(objects[i])) {
				objects[i]->Update(dt, &brickFloorCoObjects);
				continue;
			}
			if (dynamic_cast<CIntroTurtleBrack*>(objects[i])) {
				objects[i]->Update(dt, &brickFloorCoObjects);
				continue;
			}
			if (dynamic_cast<CIntroTurtleAni*>(objects[i])) {
				objects[i]->Update(dt, &brickFloorCoObjects);
				continue;
			}
			// end intro
			// start world map
			if (dynamic_cast<CMarioWorldMap*>(objects[i]))
			{
				vector<LPGAMEOBJECT> playerWorldMapCoObjects;
				playerWorldMapCoObjects.insert(playerWorldMapCoObjects.begin(), brickFloorCoObjects.begin(), brickFloorCoObjects.end());
				playerWorldMapCoObjects.insert(playerWorldMapCoObjects.begin(), portalCoObjects.begin(), portalCoObjects.end());
				objects[i]->Update(dt, &playerWorldMapCoObjects);
				continue;
			}
			// end world map

			if (dynamic_cast<CTail *>(objects[i]))
			{
				vector<LPGAMEOBJECT> tailCoObjects;
				tailCoObjects.insert(tailCoObjects.begin(), enemiesCoObjects.begin(), enemiesCoObjects.end());
				tailCoObjects.insert(tailCoObjects.begin(), turtleJumpCoObjects.begin(), turtleJumpCoObjects.end());

				tailCoObjects.insert(tailCoObjects.begin(), brickColliBrokenCoObjects.begin(), brickColliBrokenCoObjects.end());
				objects[i]->Update(dt, &tailCoObjects);
				continue;

			}
			if (dynamic_cast<CMushroom *>(objects[i]))
			{
				vector<LPGAMEOBJECT> mushroomCoObjects;
				mushroomCoObjects.insert(mushroomCoObjects.begin(), brickFloorCoObjects.begin(), brickFloorCoObjects.end());
				mushroomCoObjects.insert(mushroomCoObjects.begin(), holdCoObjects.begin(), holdCoObjects.end());
				mushroomCoObjects.insert(mushroomCoObjects.begin(), brickCoObjects.begin(), brickCoObjects.end());
				objects[i]->Update(dt, &mushroomCoObjects);
				continue;
			}
			if (dynamic_cast<CTurtle *>(objects[i]))
			{
				vector<LPGAMEOBJECT> turtleCoObjects;
				turtleCoObjects.insert(turtleCoObjects.begin(), brickFloorCoObjects.begin(), brickFloorCoObjects.end());
				turtleCoObjects.insert(turtleCoObjects.begin(), holdCoObjects.begin(), holdCoObjects.end());
				turtleCoObjects.insert(turtleCoObjects.begin(), brickCoObjects.begin(), brickCoObjects.end());
				turtleCoObjects.insert(turtleCoObjects.begin(), brickColliBrokenCoObjects.begin(), brickColliBrokenCoObjects.end());
				objects[i]->Update(dt, &turtleCoObjects);
				continue;
			}
			if (dynamic_cast<CGoombafly *>(objects[i]))
			{
				objects[i]->Update(dt, &brickFloorCoObjects);
				continue;
			}
			if (dynamic_cast<CGoomba*>(objects[i]))
			{
				objects[i]->Update(dt, &brickFloorCoObjects);
				continue;
			}
			if (dynamic_cast<CTurtleJump*>(objects[i]))
			{
				vector<LPGAMEOBJECT> turtleJumpCoObjects;
				turtleJumpCoObjects.insert(turtleJumpCoObjects.begin(), brickFloorCoObjects.begin(), brickFloorCoObjects.end());
				turtleJumpCoObjects.insert(turtleJumpCoObjects.begin(), holdCoObjects.begin(), holdCoObjects.end());
				objects[i]->Update(dt, &turtleJumpCoObjects);
				continue;
			}
			if (dynamic_cast<CMario *>(objects[i]))
			{
				vector<LPGAMEOBJECT> marioCoObjects;
				marioCoObjects.insert(marioCoObjects.begin(), brickColliBrokenCoObjects.begin(), brickColliBrokenCoObjects.end());
				marioCoObjects.insert(marioCoObjects.begin(), brickCoObjects.begin(), brickCoObjects.end());
				marioCoObjects.insert(marioCoObjects.begin(), enemiesCoObjects.begin(), enemiesCoObjects.end());
				marioCoObjects.insert(marioCoObjects.begin(), holdCoObjects.begin(), holdCoObjects.end());
				marioCoObjects.insert(marioCoObjects.begin(), brickFloorCoObjects.begin(), brickFloorCoObjects.end());
				marioCoObjects.insert(marioCoObjects.begin(), turtleJumpCoObjects.begin(), turtleJumpCoObjects.end());
				marioCoObjects.insert(marioCoObjects.begin(), portalCoObjects.begin(), portalCoObjects.end());
				marioCoObjects.insert(marioCoObjects.begin(), flowSwitchSceneCoObjects.begin(), flowSwitchSceneCoObjects.end());

				objects[i]->Update(dt, &marioCoObjects);
				continue;
			}
			
			objects[i]->Update(dt, &otherCoObjects);
		}
	}
	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL)
		return;
	// Update camera to follow mario
	float cx, cy;
	player->GetPosition(cx, cy);

	CGame *game = CGame::GetInstance();
	cx -= game->GetScreenWidth() / 2;
	cy -= game->GetScreenHeight() / 2;
	LPSCENE curentScene = CGame::GetInstance()->GetCurrentScene();
	int sceneID = curentScene->getCurrentID();
	
	if (sceneID == WORLD1 && cx > 0.0f && cx < 2564.f)
	{
		CGame::GetInstance()->SetCamPos((int)cx, 0.0f /*cy*/);
	}
	else if (sceneID == WORLD2 && cx > 0.0f && cx < 209.f)
	{
		CGame::GetInstance()->SetCamPos((int)cx, 0.0f /*cy*/);
	}
	else if (sceneID == INTRO_BACKGROUND && cx > 0.0f && cx < 128.f)
	{
		//CGame::GetInstance()->SetCamPos((int)cx, 0.0f /*cy*/);
	}
}

void CPlayScene::LoadResourcesTitledMap(int tileMapID)
{
	CTextures *textures = CTextures::GetInstance();
	CSprites *sprites = CSprites::GetInstance();
	ifstream inFile;
	if (tileMapID == WORLD1) {
		int value;
		vector<int> temp1;
		vector<vector<int>> Stage1Pos;
		inFile.open(pathBackground);
		while (inFile >> value)
		{
			temp1.push_back(value);
			if (temp1.size() == TILE_MAP_SCENE_1_SQUARE)
			{
				Stage1Pos.push_back(temp1);
				temp1.clear();
			}
		}
		LPDIRECT3DTEXTURE9 texturesBackgroundID = textures->Get(555);
		vector<LPSPRITE> Stage1Sprite;
		for (int i = 0; i < NUMBER_77; i++)
		{
			sprites->Add(55500 + i, i * NUMBER_16, 0, (i + 1) * NUMBER_16, NUMBER_16, texturesBackgroundID);
			Stage1Sprite.push_back(sprites->Get(55500 + i));
		}
		background = new CBackground(Stage1Sprite, Stage1Pos);
	}

	else if(tileMapID == WORLD2) {
		int value;
		vector<int> temp1;
		vector<vector<int>> Stage1Pos;
		inFile.open(pathBackground);
		while (inFile >> value)
		{
			temp1.push_back(value);
			if (temp1.size() == NUMBER_32)
			{
				Stage1Pos.push_back(temp1);
				temp1.clear();
			}
		}
		LPDIRECT3DTEXTURE9 texturesBackgroundID = textures->Get(556);
		vector<LPSPRITE> Stage1Sprite;
		for (int i = 0; i < 6; i++)
		{
			sprites->Add(55600 + i, i * NUMBER_16, 0, (i + 1) * NUMBER_16, NUMBER_16, texturesBackgroundID);
			Stage1Sprite.push_back(sprites->Get(55600 + i));
		}
		background = new CBackground(Stage1Sprite, Stage1Pos);
	}
	else if (tileMapID == INTRO_BACKGROUND) {
		int value;
		vector<int> temp1;
		vector<vector<int>> Stage1Pos;
		inFile.open(pathBackground);
		while (inFile >> value)
		{
			temp1.push_back(value);
			if (temp1.size() == 32)
			{
				Stage1Pos.push_back(temp1);
				temp1.clear();
			}
		}
		LPDIRECT3DTEXTURE9 texturesBackgroundID = textures->Get(556);
		vector<LPSPRITE> Stage1Sprite;
		for (int i = 0; i < NUMBER_6; i++)
		{
			sprites->Add(55600 + i, i * NUMBER_16, 0, (i + 1) * NUMBER_16, NUMBER_16, texturesBackgroundID);
			Stage1Sprite.push_back(sprites->Get(55600 + i));
		}
		background = new CBackground(Stage1Sprite, Stage1Pos);
	}
	else if (tileMapID == WORLD4) {
		int value;
		vector<int> temp1;
		vector<vector<int>> Stage1Pos;
		inFile.open(pathBackground);
		while (inFile >> value)
		{
			temp1.push_back(value);
			if (temp1.size() == NUMBER_16)
			{
				Stage1Pos.push_back(temp1);
				temp1.clear();
			}
		}
		LPDIRECT3DTEXTURE9 texturesBackgroundID = textures->Get(4);
		vector<LPSPRITE> Stage1Sprite;
		for (int row = 0; row < NUMBER_4; row++ ) {
			for (int i = 0; i < NUMBER_8; i++)
			{
				sprites->Add(4000 + i + row*NUMBER_8, i * NUMBER_16, row * NUMBER_16, (i + NUMBER_1) * NUMBER_16, row * NUMBER_16 + NUMBER_16, texturesBackgroundID);
				Stage1Sprite.push_back(sprites->Get(4000 + i + row * NUMBER_8));
			}
		}
		background = new CBackground(Stage1Sprite, Stage1Pos);
	}
	
}

void CPlayScene::AddObject(LPGAMEOBJECT gameObject)
{
	objects.push_back(gameObject);
}

void CPlayScene::Render()
{
	background->Render();
	for (int i = 0; i < objects.size(); i++) {
		// DebugOut(L"%d", i);
		/*if (player != NULL) {
		float a  = abs( objects[i]->x - player->x);
		if (a > NUMBER_250) continue;

		}*/
		objects[i]->Render();
	}
}

/*
	Unload current scene
*/
void CPlayScene::Unload()
{
	for (int i = 0; i < objects.size(); i++){
		if (dynamic_cast<CHud*>(objects[i])) {
			CHud* chub = dynamic_cast<CHud*>(objects[i]);
			chub->~CHud();
			continue;
		}
		// if (dynamic_cast<CMarioWorldMap*>(objects[i])) {
		// 	continue;
		// }
		delete objects[i];
	}

	objects.clear();
	player = NULL;

	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);
}

void CPlayScenceKeyHandler::OnKeyDown(int KeyCode)
{
	CMario *mario = ((CPlayScene *)scence)->GetPlayer();
	CMarioWorldMap* marioWorldMap = ((CPlayScene*)scence)->GetPlayerWorldMap();
	if (mario != NULL) {
		switch (KeyCode)
		{
		case DIK_X:
			mario->SetState(MARIO_STATE_JUMP);
			break;
		case DIK_Z:
			mario->StartAttact();
			mario->SetState(MARIO_STATE_ATTACT);
			break;
		case DIK_C:
			mario->SetIsActiveFly(false);
			break;
		case DIK_S:
			mario->SetState(MARIO_STATE_JUMP_HEIGHT);
			break;
		case DIK_1:
			float level1X, level1Y;
			mario->GetPosition(level1X, level1Y);
			mario->SetPosition(level1X, level1Y - NUMBER_40);
			mario->SetLevel(MARIO_LEVEL_1);
			break;
		case DIK_2:
			float level2X, level2Y;
			mario->GetPosition(level2X, level2Y);
			mario->SetPosition(level2X, level2Y - NUMBER_40);
			mario->SetLevel(MARIO_LEVEL_2);
			break;
		case DIK_3:
			float level3X, level3Y;
			mario->GetPosition(level3X, level3Y);
			mario->SetPosition(level3X, level3Y - NUMBER_40);
			mario->SetLevel(MARIO_LEVEL_3);
			break;
		case DIK_4:
			mario->SetPosition(NUMBER_1000, NUMBER_20);
			break;
		case DIK_5:
			mario->SetPosition(NUMBER_2000, NUMBER_20);
			break;
		 case DIK_Q:
		 	mario->Reset();
		 	break;
		}
	}
	if (marioWorldMap != NULL) {
		switch (KeyCode)
		{
		case DIK_RETURN:
			marioWorldMap->SetState(WORLD_MAP_MARIO_SWITCH_SCENE);
			break;
		default:
			break;
		}
	}
}

void CPlayScene::Pause()
{
	isPause = true;
	pauseStartAt = GetTickCount();
}

void CPlayScene::UnPause()
{
	if (isPause && pauseStartAt + STOP_TIME_DURATION < GetTickCount())
	{
		isPause = false;
	}
}

void CPlayScenceKeyHandler::KeyState(BYTE *states)
{
	CGame *game = CGame::GetInstance();
	CMario *mario = ((CPlayScene *)scence)->GetPlayer();
	if (mario != NULL) {
		mario->SetFast(false);
		if (mario->GetState() == MARIO_STATE_DIE)
			return;
		if (game->IsKeyDown(DIK_RIGHT))
		{
			// if (mario->GetState() == MARIO_STATE_FLY) return;
			if (game->IsKeyDown(DIK_A))
			{
				mario->SetFast(true);
			}
			mario->SetState(MARIO_STATE_WALKING_RIGHT);
		}
		else if (game->IsKeyDown(DIK_LEFT))
		{
			if (game->IsKeyDown(DIK_A))
			{
				mario->SetFast(true);
			}
			mario->SetState(MARIO_STATE_WALKING_LEFT);
		}
		else if (game->IsKeyDown(DIK_DOWN))
		{
			// 
			// DebugOut(L"state Mario: %d \n", mario->GetState());
			mario->SetState(MARIO_STATE_SIT_DOWN);
		}
		else if (game->IsKeyDown(DIK_Q))
		{
		}
		else if (game->IsKeyDown(DIK_X))
		{
			mario->SetState(MARIO_STATE_JUMP);
		/*	if (mario->GetLevel() == MARIO_LEVEL_3 && mario->vy > 0 && mario->isJump)
			{
				mario->SetState(MARIO_STATE_SWING_TAIL);
			}*/
		}
	
		else if (game->IsKeyDown(DIK_SPACE)) {
			
			int tmpLevel = mario->GetLevel();
			if (tmpLevel == MARIO_LEVEL_3 && mario->GetIsActiveFly()) {
				mario->SetState(MARIO_STATE_FLY);
			}
		}
		else
		{
			mario->SetState(MARIO_STATE_IDLE);
		}
	}

	CMarioWorldMap* marioWorldMap = ((CPlayScene*)scence)->GetPlayerWorldMap();
	

	if (marioWorldMap != NULL) {
		
		if (game->IsKeyDown(DIK_RIGHT))
		{
			marioWorldMap->SetState(WORLD_MAP_MARIO_LEVEL1_STATE_WALKING_RIGHT);
		}
		else if (game->IsKeyDown(DIK_LEFT))
		{
			marioWorldMap->SetState(WORLD_MAP_MARIO_LEVEL1_STATE_WALKING_LEFT);
		}
		else if (game->IsKeyDown(DIK_DOWN))
		{
			marioWorldMap->SetState(WORLD_MAP_MARIO_LEVEL1_STATE_WALKING_DOWN);
		}
		else if (game->IsKeyDown(DIK_UP))
		{
			marioWorldMap->SetState(WORLD_MAP_MARIO_LEVEL1_STATE_WALKING_UP);
		}
		else {
			marioWorldMap->SetState(WORLD_MAP_MARIO_LEVEL1_STATE_IDLE);
		}
	}
}