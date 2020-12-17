#include "Background.h"
#include "Game.h"
void CBackground::Render()
{
	/// **** map 1 ****
	LPSCENE curentScene = CGame::GetInstance()->GetCurrentScene();
	int sceneID = curentScene->getCurrentID();
	if (sceneID == WORLD1) {
		for (int i = 0; i < position.size(); i++) {
			for (int j = 0; j < TILE_MAP_SCENE_1_SQUARE; j++) {
				float drawX = j * NUMBER_16;
				float drawY = i * NUMBER_16;
				sprites[position[i][j]]->Draw(drawX, drawY, 255);
			}
		}
	}
	/// **** map 2 ****
	else if (sceneID == WORLD2) {
		for (int i = 0; i < position.size(); i++) {
			for (int j = 0; j < TILE_MAP_SCENE_2_SQUARE; j++) {
				float drawX = j * NUMBER_16;
				float drawY = i * NUMBER_16;
				sprites[position[i][j]]->Draw(drawX, drawY, 255);
			}
		}
	}
	/// **** world map **** 
	else if (sceneID == WORLD4) {
		for (int i = 0; i < position.size(); i++) {
			for (int j = 0; j < TILE_MAP_SCENE_WOLRD_MAP_SQUARE; j++) {
				float drawX = j * NUMBER_16;
				float drawY = i * NUMBER_16;
				// DebugOut(L"pos:%d \n", position[i][j]);
				sprites[position[i][j]]->Draw(drawX, drawY, 255);
			}
		}
	}
}

void CBackground::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + 1;
	b = y + 1;

}


