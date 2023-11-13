#include "LevelMaker.h"
#include "ExternDecl.h"

bool LevelMaker::create(SDL_Renderer* renderer, const char* tilemap[], const char* path_float, const char* path_mudUp1, const char* path_top1, const char* path_top2, const char* path_top3, const char* path_mid1, const char* path_mid2, const char* path_mid3, const char* path_bot1, const char* path_bot2, const char* path_bot3, const char* path_grassUp1, const char* path_mudDown1, const char* path_grassUp2) {

	// Shouldn't really hard-code it here, should instead be retrieved from the actual tile texture
	const float tileSize	= 16.0f;
	const float scale		= 3.125f;

	for (int count = 0; count < 11; count++) {
		for (int index = 0; index < 28; index++) {
			int x, y;

			if (tilemap[count][index] == ' ') {
				continue;
			}

			x = index * 50;
			y = count * 50;

			const char* texturePath = nullptr;

				 if (tilemap[count][index] == '1') texturePath = path_top1;
			else if (tilemap[count][index] == '2') texturePath = path_top2;
			else if (tilemap[count][index] == '3') texturePath = path_top3;
			else if (tilemap[count][index] == '4') texturePath = path_mid1;
			else if (tilemap[count][index] == '5') texturePath = path_mid2;
			else if (tilemap[count][index] == '6') texturePath = path_mid3;
			else if (tilemap[count][index] == '7') texturePath = path_bot1;
			else if (tilemap[count][index] == '8') texturePath = path_bot2;
			else if (tilemap[count][index] == '9') texturePath = path_bot3;
			else if (tilemap[count][index] == '(') texturePath = path_grassUp1;
			else if (tilemap[count][index] == '>') texturePath = path_mudDown1;
			else if (tilemap[count][index] == ')') texturePath = path_grassUp2;
			else if (tilemap[count][index] == '{') texturePath = path_mudUp1;
			else if (tilemap[count][index] == '-') texturePath = path_float;

			if (texturePath)
			{
				Tile* tile = new Tile;
				if (!tile->create(x, y, texturePath, scale, renderer))
					return false;

				group_of_tiles.push_back(tile);
			}
		}
	}

	size.x = 28 * (int)(tileSize * scale);
	size.y = 11 * (int)(tileSize * scale);

	return true;
}

void LevelMaker::destroy() {
	for(uint32_t i = 0; i < group_of_tiles.size(); ++i)
	{
		delete group_of_tiles[i];
	}

	group_of_tiles.clear();
}