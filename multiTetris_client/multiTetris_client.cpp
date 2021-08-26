
#include <mutex>
#include <vector>
#include "tetrisUtil.h"
#include "socketClass.h"

#define BUFFERSIZE 1024
using namespace std;

bool run;
bool white_space;
mutex m;

void drawBlock(block blo, int basePos=0) {
	for (int i = 0; i < BLOCK_SIZE_Y; i++) {
		for (int j = 0; j < BLOCK_SIZE_X; j++) {
			if (blocks[blo.getBlockType()][blo.getRotation()][i][j] == CONTROL_BLOCK) {
				setCursor((blo.getXpos() + j + basePos) * 2, blo.getYpos() + i);
				printf("□");
			}
		}
	}
}
void removeBlock(block blo, int basePos=0) {
	for (int i = 0; i < BLOCK_SIZE_X; i++) {
		for (int j = 0; j < BLOCK_SIZE_Y; j++) {
			if (blocks[blo.getBlockType()][blo.getRotation()][i][j] == CONTROL_BLOCK) {
				setCursor((blo.getXpos() + j + basePos) * 2, blo.getYpos() + i);
				printf("  ");
			}
		}
	}
}
void drawBlockShadow(block blo, int basePos=0) {
	for (int i = 0; i < BLOCK_SIZE_Y; i++) {
		for (int j = 0; j < BLOCK_SIZE_X; j++) {
			if (blocks[blo.getBlockType()][blo.getRotation()][i][j] == CONTROL_BLOCK) {
				setCursor((blo.getXpos() + j + basePos) * 2, blo.getYpos() + i);
				printf("▩");
			}
		}
	}
}

void draw(block* blo, mapData* map, int pos) {
	while (run) {
		for (int i = 0; i < MAP_SIZE_Y; i++) {
			for (int j = 0; j < MAP_SIZE_X; j++) {
				m.lock();
				setCursor((j+ pos) * 2, i);
				switch (map->getMap()[i][j]) {
				case SPACE: {
					if (white_space) { 
						printf("  ");
					}
					break; 
				}
				case WALL: printf("▧"); break;
				case CONTROL_BLOCK: printf("□"); break;
				case STACKED_BLOCK: printf("■"); break;
				default: break;
				}
				m.unlock();
			}
			printf("\n");
		}
		white_space = false;
		Sleep(30);
	}
}
void gameRun(gameSettings* set, block* blo, mapData* map, int basePos) {
	while (run) {
		Sleep(set->getGameSpeed());
		if (!map->checkBlock(*blo, 0, 1)) {
			m.lock();
			removeBlock(*blo, basePos);
			removeBlock(map->getShadowBlock(*blo), basePos);
			blo->dropDown();
			drawBlock(*blo, basePos);
			drawBlockShadow(map->getShadowBlock(*blo), basePos);
			m.unlock();
		}
		else {
			map->putBlock(*blo);
			set->scoreUp(map->checkLine().size());
			map->collapseBlock(map->checkLine());
			blo->initial();
		}
		//m.lock();
		//setCursor(40, 0);
		//cout << "게임레벨 : " << set->getGameLevel();
		//setCursor(40, 1);
		//cout << "스코어 : " << set->getScore();
		//m.unlock();
	}
}
void receiveData(SOCKET sock, block b, mapData m) {
	char x;
	vector<char> buffer;

	while (run) {
		if (recv(sock, &x, sizeof(char), 0) == SOCKET_ERROR)
		{
			cout << "error" << endl;
			break;
		}
		if (x != 'C') {
			buffer.push_back(x);
		}

		else {
			
		}
	}
}

int main()
{
	run = true;
	white_space = false;
	CursorView(0);

	mapData map(MAP_SIZE_X, MAP_SIZE_Y);
	map.initial();
	mapData mapOpp(MAP_SIZE_X, MAP_SIZE_Y);
	mapOpp.initial();

	block b;
	block bOpp;
	gameSettings gameSet;
	gameSettings gameSetOpp;

	thread thread_draw = thread(draw, &b, &map, 0);
	thread thread_drawOpp = thread(draw, &bOpp, &mapOpp, MAP_SIZE_X+3);
	thread thread_game = thread(gameRun, &gameSet, &b, &map, 0);
	thread thread_gameOpp = thread(gameRun, &gameSetOpp, &bOpp, &mapOpp, MAP_SIZE_X+3);

	while (run) {
		int key = _getch();
		if (key == 224) {
			switch (_getch()) {
			case 72/*UP*/: {
				m.lock();
				removeBlock(b);
				removeBlock(map.getShadowBlock(b));
				b.rotate();
				drawBlock(b);
				drawBlockShadow(map.getShadowBlock(b));
				m.unlock();
				break;
			}
			case 75/*LEFT*/: {
				if (!map.checkBlock(b,-1,0)) {
					m.lock();
					removeBlock(b);
					removeBlock(map.getShadowBlock(b));
					b.move(-1, 0);
					drawBlock(b);
					drawBlockShadow(map.getShadowBlock(b));
					m.unlock();
				}
				break;
			}
			case 77/*RIGHT*/: {
				if (!map.checkBlock(b, 1, 0)) {
					m.lock();
					removeBlock(b);
					removeBlock(map.getShadowBlock(b));
					b.move(1, 0);
					drawBlock(b);
					drawBlockShadow(map.getShadowBlock(b));
					m.unlock();
				}
				break;
			}
			case 80/*DOWN*/: {
				if (!map.checkBlock(b, 0, 1)) {
					m.lock();
					removeBlock(b);
					removeBlock(map.getShadowBlock(b));
					b.move(0, 1);
					drawBlock(b);
					drawBlockShadow(map.getShadowBlock(b));
					m.unlock();
				}
				break;
			}
			}
		}
		else if (key == 32) {
			m.lock();
			removeBlock(b);
			removeBlock(map.getShadowBlock(b));
			m.unlock();
			map.putBlock(b);
			white_space = true;
			gameSet.scoreUp(map.checkLine().size());
			map.collapseBlock(map.checkLine());
			b.initial();
		}
		else if((char)key == 'q'){
			run = false;
			thread_draw.join();
			thread_drawOpp.join();
			thread_game.join();
			thread_gameOpp.join();
		}
		//cout << key;
	}
}




