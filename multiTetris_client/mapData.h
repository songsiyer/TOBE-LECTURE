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
	mapData(int x_size, int y_size); //���߹迭 �����Ҵ�
	~mapData();						 // �����Ҵ��� �迭 free

	void initial();//
	void popLine(int y_pos);
	void pushLine(int y_pos);
	void collapseBlock(std::vector<int> lines);

	bool checkBlock(block block, int x_add_pos, int y_add_pos);
	bool putBlock(block block); // y�� ���ϴ����� �̵��� �ʿ� �ִ´�.
	block getShadowBlock(block block);
	std::vector<int> checkLine();


	/********************get - set*********************/
	int** getMap();				//��� �� ������ ������ ���� �� �� ����.


};

