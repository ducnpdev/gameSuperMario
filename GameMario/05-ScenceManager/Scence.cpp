#include "Scence.h"

CScene::CScene(int id, LPCWSTR filePath, LPCWSTR pathBackground)
{
	this->id = id;
	this->sceneFilePath = filePath;
	this->pathBackground = pathBackground;
}