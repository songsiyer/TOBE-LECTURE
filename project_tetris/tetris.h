#pragma once
//�� ���� ��� �� ����
#define SPACE 0
#define WALL 1
#define CONTROL_BLOCK 2
#define STACKED_BLOCK 3

//�� ũ��
#define MAP_SIZE_X 20
#define MAP_SIZE_Y 40

//�� ũ��
#define BLOCK_SIZE_X 4
#define BLOCK_SIZE_Y 4

//�� Ÿ�� ����
typedef int BLOCK[BLOCK_SIZE_X][BLOCK_SIZE_Y];

// L��� ��
#define L_BLOCK_0 {{2,0,0,0},{2,0,0,0},{2,2,0,0},{0,0,0,0}}
#define L_BLOCK_1 {{2,2,2,0},{2,0,0,0},{0,0,0,0},{0,0,0,0}}
#define L_BLOCK_2 {{2,2,0,0},{0,2,0,0},{0,2,0,0},{0,0,0,0}}
#define L_BLOCK_3 {{0,0,0,0},{0,0,0,2},{0,2,2,2},{0,0,0,0}}

// ���ڸ�� ��
#define I_BLOCK_0 {{2,0,0,0},{2,0,0,0},{2,0,0,0},{2,0,0,0}}
#define I_BLOCK_1 {{2,2,2,2},{0,0,0,0},{0,0,0,0},{0,0,0,0}}
#define I_BLOCK_2 {{2,0,0,0},{2,0,0,0},{2,0,0,0},{2,0,0,0}}
#define I_BLOCK_3 {{2,2,2,2},{0,0,0,0},{0,0,0,0},{0,0,0,0}}

// ���簢��� ��
#define SQ_BLOCK_0 {{2,2,0,0},{2,2,0,0},{0,0,0,0},{0,0,0,0}}
#define SQ_BLOCK_1 {{2,2,0,0},{2,2,0,0},{0,0,0,0},{0,0,0,0}}
#define SQ_BLOCK_2 {{2,2,0,0},{2,2,0,0},{0,0,0,0},{0,0,0,0}}
#define SQ_BLOCK_3 {{2,2,0,0},{2,2,0,0},{0,0,0,0},{0,0,0,0}}

// L��������� ��
#define RL_BLOCK_0 {{0,2,0,0},{0,2,0,0},{2,2,0,0},{0,0,0,0}}
#define RL_BLOCK_1 {{2,0,0,0},{2,2,2,0},{0,0,0,0},{0,0,0,0}}
#define RL_BLOCK_2 {{2,2,0,0},{2,0,0,0},{2,0,0,0},{0,0,0,0}}
#define RL_BLOCK_3 {{2,2,2,0},{0,0,2,0},{0,0,0,0},{0,0,0,0}}

// �Ǹ�� ��
#define H_BLOCK_0 {{0,2,0,0},{2,2,2,0},{0,0,0,0},{0,0,0,0}}
#define H_BLOCK_1 {{2,0,0,0},{2,2,0,0},{2,0,0,0},{0,0,0,0}}
#define H_BLOCK_2 {{2,2,2,0},{0,2,0,0},{0,0,0,0},{0,0,0,0}}
#define H_BLOCK_3 {{0,2,0,0},{2,2,0,0},{0,2,0,0},{0,0,0,0}}

// ������׸�� ��
#define Z_BLOCK_0 {{0,2,2,0},{2,2,0,0},{0,0,0,0},{0,0,0,0}}
#define Z_BLOCK_1 {{2,0,0,0},{2,2,0,0},{0,2,0,0},{0,0,0,0}}
#define Z_BLOCK_2 {{0,2,2,0},{2,2,0,0},{0,0,0,0},{0,0,0,0}}
#define Z_BLOCK_3 {{2,0,0,0},{2,2,0,0},{0,2,0,0},{0,0,0,0}}

int blocks[6][4][4][4] = { {L_BLOCK_0,L_BLOCK_1,L_BLOCK_2,L_BLOCK_3},
							{I_BLOCK_0,I_BLOCK_1,I_BLOCK_2,I_BLOCK_3},
							{SQ_BLOCK_0,SQ_BLOCK_1,SQ_BLOCK_2,SQ_BLOCK_3},
							{RL_BLOCK_0,RL_BLOCK_1,RL_BLOCK_2,RL_BLOCK_3},
							{H_BLOCK_0,H_BLOCK_1,H_BLOCK_2,H_BLOCK_3},
							{Z_BLOCK_0,Z_BLOCK_1,Z_BLOCK_2,Z_BLOCK_3} };
