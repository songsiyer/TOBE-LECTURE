#pragma once
#include "block.h"
#include "tetrisData.h"
#include <vector>
#include <iostream>

class mapData
{
private:
	int x_size;
	int y_size;
	int** mapArray;

public:
	mapData(int x_size, int y_size); //이중배열 동적할당
	~mapData();						 // 동적할당한 배열 free

	void initial();//
	void popLine(int y_pos);
	void pushLine(int y_pos);
	void collapseBlock(std::vector<int> lines);

	bool checkBlock(block block, int x_add_pos, int y_add_pos);
	bool putBlock(block block); // y값 최하단으로 이동후 맵에 넣는다.
	block getShadowBlock(block block);
	std::vector<int> checkLine();


	/********************get - set*********************/
	int** getMap();				//어떻게 잘 밖으로 데이터 전달 할 것 인지.


};

