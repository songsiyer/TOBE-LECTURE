#include "block.h"

block::block()
{
	x_pos = (MAP_SIZE_X - 2) / 2;
	y_pos = 1;
	rotation = 0;
	srand((unsigned)time(NULL));
	block_type = rand() % 6;
}


block::~block()
{
}

void block::initial()
{
	x_pos = (MAP_SIZE_X - 2) / 2;
	y_pos = 1;
	rotation = 0;
	srand((unsigned)time(NULL));
	block_type = rand() % 6;
}

void block::move(int x_pos, int y_pos)
{
	this->x_pos += x_pos;
	this->y_pos += y_pos;
}

void block::rotate()
{
	if (rotation >= 3) {
		rotation = 0;
	}
	else {
		rotation++;
	}
}

void block::dropDown()
{
	y_pos++;
}
