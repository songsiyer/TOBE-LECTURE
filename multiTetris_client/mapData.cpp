#include "mapData.h"

mapData::mapData(int x_size, int y_size)
{
	this->x_size = x_size;
	this->y_size = y_size;

    mapArray = (int**)malloc(sizeof(int*) * y_size);
	if (mapArray != NULL) {
		for (int i = 0; i < y_size; i++)
		{
			mapArray[i] = (int*)malloc(sizeof(int) * x_size);
		}
	}
}

mapData::~mapData()
{
    for (int i = 0; i < y_size; i++)
    {
        free(mapArray[i]);
    }
    free(mapArray);
}

void mapData::initial()
{
	for (int i = 0; i < y_size; i++) {
		for (int j = 0; j < x_size; j++) {
			if (i == 0 || i == y_size - 1 || j == 0 || j == x_size - 1) {
				mapArray[i][j] = WALL;
			}
			else {
				mapArray[i][j] = SPACE;
			}
		}
	}
}

void mapData::popLine(int y_pos)
{
	for (int i = 1; i < x_size-1; i++) {
		mapArray[y_pos][i] = SPACE;
	}
}

void mapData::pushLine(int y_pos)
{
}

void mapData::collapseBlock(std::vector<int> lines)
{
	for (int i = 0; i < lines.size()-1; i++) {

		for (int j = lines[i]; j > lines[i + 1]; j--) {
			if ((j - 1 >= lines[i + 1])&& j - (i + 1) > 0) {
				memcpy(mapArray[j], mapArray[j - (i + 1)], sizeof(int) * x_size);
			}
		}
	}
}

bool mapData::checkBlock(block block, int x_add_pos, int y_add_pos)
{
	for (int i = (BLOCK_SIZE_X - 1); i >= 0; i--) {
		for (int j = (BLOCK_SIZE_Y - 1); j >= 0; j--) {
			if (blocks[block.getBlockType()][block.getRotation()][i][j] == CONTROL_BLOCK
				&& (mapArray[block.getYpos() +y_add_pos + i][block.getXpos() + x_add_pos + j] == WALL 
					|| mapArray[block.getYpos() + y_add_pos + i][block.getXpos() + x_add_pos + j] == STACKED_BLOCK)) {
				return true;
			}
		}
	}
	return false;
}

bool mapData::putBlock(block block)
{
	int shadow_y = 0;
	for (int i = 0; i < MAP_SIZE_Y- block.getYpos(); i++) {
		if (checkBlock(block,0, i+1)) {
			shadow_y = i;
			break;
		}
	}

	for (int i = 0; i < BLOCK_SIZE_Y; i++) {
		for (int j = 0; j < BLOCK_SIZE_X; j++) {
			if (blocks[block.getBlockType()][block.getRotation()][i][j] == CONTROL_BLOCK) {
				mapArray[block.getYpos()+shadow_y + i][block.getXpos() + j] = STACKED_BLOCK;
			}
		}
	}

	return false;
}

block mapData::getShadowBlock(block blo)
{
	block shadow = blo;
	int shadow_y = 0;
	for (int i = 0; i < MAP_SIZE_Y - blo.getYpos(); i++) {
		if (checkBlock(blo, 0, i + 1)) {
			shadow_y = i;
			break;
		}
	}
	shadow.setYpos(blo.getYpos()+shadow_y);
	return shadow;
}

std::vector<int> mapData::checkLine()
{
	int result;
	std::vector<int> resultList = std::vector<int>();
	for (int i = y_size-1; i > 0; i--) {
		result = 0;
		for (int j = 1; j < x_size-1; j++) {
			result += mapArray[i][j];
		}
		if (result == STACKED_BLOCK * (x_size - 2)) {
			resultList.push_back(i);
		}
	}
	resultList.push_back(1);
	return resultList;
}

int** mapData::getMap()
{
	return mapArray;
}
