#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>
#include "tetris.h"

int map[MAP_SIZE_Y][MAP_SIZE_X];

struct block_info {

	int block_pos_x;
	int block_pos_y;
	int block_rotation;
	int current_block_type;

	void rotate() {
		block_rotation = ++block_rotation % 4;
	}
	void toRight() {
		block_pos_x++;
	}
	void toLeft() {
		block_pos_x--;
	}
	void toDown() {
		block_pos_y++;
	}
	void initBlock() {
		block_pos_x = (MAP_SIZE_X - 2) / 2;
		block_pos_y = 1;
		block_rotation = 0;
		current_block_type = rand() % 6;
	}
};

void CursorView(char show)
{
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;

	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

void clearMap() {
	for (int i = 0; i < MAP_SIZE_Y; i++) {
		for (int j = 0; j < MAP_SIZE_X; j++) {
			if (i == 0 || i == MAP_SIZE_Y-1 || j == 0 || j == MAP_SIZE_X-1) {
				map[i][j] = WALL;
			}
			else {
				map[i][j] = SPACE;
			}
		}
	}
}
void drawMap() {
	for (int i = 0; i < MAP_SIZE_Y; i++) {
		for (int j = 0; j < MAP_SIZE_X; j++) {
			setCursor(j*2,i);
			switch (map[i][j]) {
			case SPACE			: printf("  "); break;
			case WALL			: printf("▧"); break;
			case CONTROL_BLOCK	: printf("□"); break;
			case STACKED_BLOCK	: printf("■"); break;
			default: break;
			}
		}
		printf("\n");
	}
}
void setCursor(int x, int y) {
	COORD pos = { x,y };//구조체 class
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
bool checkBlock(int x, int y, int block_type, int rotation) {
	for (int i = (BLOCK_SIZE_X - 1); i >= 0; i--) {
		for (int j = (BLOCK_SIZE_Y - 1); j >= 0; j--) {
			if (blocks[block_type][rotation][i][j] == CONTROL_BLOCK
				&& (map[y + i][x + j] == WALL || map[y + i][x + j] == STACKED_BLOCK)) {
				return true;
			}
		}
	}
	return false;
}
void drawBlock(int x, int y, int block_type, int rotation) {
	for (int i = 0; i < BLOCK_SIZE_Y; i++) {
		for (int j = 0; j < BLOCK_SIZE_X; j++) {
			if (blocks[block_type][rotation][i][j] == CONTROL_BLOCK) {
				setCursor((x + j) * 2, y + i);
				printf("□");
			}
		}
	}
}
void drawBlockShadow(int x, int y, int block_type, int rotation) {
	int shadow_y = 0;
	for (int i = y; i <MAP_SIZE_Y; i++) {
		if (checkBlock(x, i, block_type, rotation)) {
			shadow_y = i-1;
			break;
		}
	}

	for (int i = 0; i < BLOCK_SIZE_Y; i++) {
		for (int j = 0; j < BLOCK_SIZE_X; j++) {
			if (blocks[block_type][rotation][i][j] == CONTROL_BLOCK) {
				setCursor((x + j) * 2, shadow_y + i);
				printf("▩");
			}
		}
	}
}
void removeBlock(int x, int y , int block_type, int rotation) {
	
	for (int i = 0; i < BLOCK_SIZE_X; i++) {
		for (int j = 0; j < BLOCK_SIZE_Y; j++) {
			if (blocks[block_type][rotation][i][j] == CONTROL_BLOCK) {
				setCursor((x + j) * 2, y + i);
				printf("  ");
			}
		}
	}
}
int removeBlockShadow(int x, int y, int block_type, int rotation) {
	int shadow_y = 0;
	for (int i = y; i < MAP_SIZE_Y; i++) {
		if (checkBlock(x, i, block_type, rotation)) {
			shadow_y = i - 1;
			break;
		}
	}

	for (int i = 0; i < BLOCK_SIZE_Y; i++) {
		for (int j = 0; j < BLOCK_SIZE_X; j++) {
			if (blocks[block_type][rotation][i][j] == CONTROL_BLOCK) {
				setCursor((x + j) * 2, shadow_y + i);
				printf("  ");
			}
		}
	}
	return shadow_y;
}
void putBlockToMap(int x, int y, int block_type, int rotation) {
	for (int i = 0; i < BLOCK_SIZE_X; i++) {
		for (int j = 0; j < BLOCK_SIZE_Y; j++) {
			if (blocks[block_type][rotation][i][j] == CONTROL_BLOCK) {
				map[y + i][x + j] = STACKED_BLOCK;
			}
		}
	}
}
char keyAction(int *current_x, int* current_y, int current_block_type, int* block_rotation) {
	int key = _getch();
	
	if (key == 224) {
		//printf("%d", _getch());
		switch(_getch()) {
		case 72/*UP*/: {
			removeBlockShadow(*current_x, *current_y, current_block_type, *block_rotation);
			*block_rotation = ++(*block_rotation) % 4;
			break;
		}
		case 75/*LEFT*/: {
			if (!checkBlock((*current_x) -1, *current_y, current_block_type, *block_rotation)) {
				removeBlockShadow(*current_x, *current_y, current_block_type, *block_rotation);
				(*current_x)--;
			}
			break;
		}
		case 77/*RIGHT*/: {
			if (!checkBlock((*current_x) + 1, *current_y, current_block_type, *block_rotation)) {
				removeBlockShadow(*current_x, *current_y, current_block_type, *block_rotation);
				(*current_x)++;
			}
			break; 
		}
		case 80/*DOWN*/: {
			if(!checkBlock(*current_x, (*current_y)+1, current_block_type, *block_rotation))
			*current_y += 1;
			break;
		}
		}
		return '~';
	}
	else if (key == 32) {
		putBlockToMap(*current_x, removeBlockShadow(*current_x, *current_y, current_block_type, *block_rotation), current_block_type, *block_rotation);
		return key;
	}
	else {
		return key;
	}
}
void drawBlock(block_info block) {
	for (int i = 0; i < BLOCK_SIZE_Y; i++) {
		for (int j = 0; j < BLOCK_SIZE_X; j++) {
			if (blocks[block.current_block_type][block.block_rotation][i][j] == CONTROL_BLOCK) {
				setCursor((block.block_pos_x + j) * 2, block.block_pos_y + i);
				printf("□");
			}
		}
	}
}
void removeBlock(block_info block) {

	for (int i = 0; i < BLOCK_SIZE_X; i++) {
		for (int j = 0; j < BLOCK_SIZE_Y; j++) {
			if (blocks[block.current_block_type][block.block_rotation][i][j] == CONTROL_BLOCK) {
				setCursor((block.block_pos_x + j) * 2, block.block_pos_y + i);
				printf("  ");
			}
		}
	}
}
char keyAction(block_info* block) {
	int key = _getch();
	if (key == 224) {
		//printf("%d", _getch());
		switch (_getch()) {
		case 72/*UP*/: {
			
			block->rotate();
			break;
		}
		case 75/*LEFT*/: {
			block->toLeft();
			break;
		}
		case 77/*RIGHT*/: {
			block->toRight();
			break;
		}
		case 80/*DOWN*/: {
			block->toDown();
			break;
		}
		}
		return ' ';
	}
	else {

		return key;
	}
}
void checkMapAndDraw(int x) {
	for (int i = x; i < x + BLOCK_SIZE_X; i++) {
		for (int j = 0; j < MAP_SIZE_Y; j++) {

		}
	}
}
void reMap(int remap_position_y) {
	for (int i = remap_position_y; i > 1; i--) {
		for (int j = 0; j < MAP_SIZE_X; j++) {
			map[i][j] = map[i - 1][j];
		}
	}
	drawMap();
}
void checkComplete() {
	for (int i = 0; i < MAP_SIZE_Y; i++) {
		int stack_count = 0;
		for (int j = 0; j < MAP_SIZE_X; j++) {
			if (map[i][j] == STACKED_BLOCK)stack_count++;
		}
		if (stack_count == MAP_SIZE_X-2) {
			for (int j = 1; j < MAP_SIZE_X-1; j++) {
				map[i][j] = SPACE;
			}
			drawMap();
			Sleep(20);
			reMap(i);
		}
	}
}
void downRow(int y_pos) {
	for (int i = y_pos-1; i > 1; i--) {
		for (int j = 1; j < MAP_SIZE_X - 1; j++) {
			map[i][j] = map[i - 1][j];
		}
	}
	//Sleep(30);
}
void checkRow() {
	for (int i = MAP_SIZE_Y - 1; i > 1; i--) {
		for (int j = 1; j < MAP_SIZE_X - 1; j++) {
			if (map[i][j] == 0) break;
			if (j == MAP_SIZE_X - 2) downRow(i);
		}
	}
	drawMap();
}

int main(int argc, char* argv[])
{
	CursorView(0);
	char option_key = ' ';
	int input_delay = 50;
	int drop_count = 20;

	srand((unsigned)time(NULL)); //랜덤 시드설정
	int block_pos_x = (MAP_SIZE_X - 2) / 2;
	int block_pos_y = 1;
	int block_rotation = 0;
	int current_block_type = rand()%6;
	block_info block;
	block.initBlock();

	clearMap();
	drawMap();

	while (option_key != 'q') {
		for (int i = 0; i < drop_count; i++) {
			if (_kbhit()) { //키입력이 있을때
				removeBlock(block);
				option_key = keyAction(&block_pos_x, &block_pos_y, current_block_type, &block_rotation);
				if (option_key == 32) {
					block_pos_x = (MAP_SIZE_X - 2) / 2;
					block_pos_y = 1;
					current_block_type = rand() % 6;
					block_rotation = 0;
					drawMap();
					checkComplete();
				}
				else {
					drawBlock(block);
					drawBlockShadow(block_pos_x, block_pos_y, current_block_type, block_rotation);
				}
				removeBlock(block);
				option_key = keyAction(&block);
				drawBlock(block);
			}
			Sleep(input_delay);
		}
		removeBlock(block);
		//시간지나서 한칸 내려갈때
		if (checkBlock(block_pos_x, block_pos_y+1, current_block_type, block_rotation)) {
			putBlockToMap(block_pos_x, block_pos_y, current_block_type, block_rotation);
			
			block_pos_x = (MAP_SIZE_X - 2) / 2;
			block_pos_y = 1;
			current_block_type = rand() % 6;
			block_rotation = 0;
			drawMap();
			checkRow();
			//checkComplete();
		}
		else {
			block_pos_y++;
			drawBlock(block);
			drawBlockShadow(block_pos_x, block_pos_y, current_block_type, block_rotation);
		}
	}
}