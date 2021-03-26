#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>
#include <math.h>

#define SNAIL_SIZE 5
#define MAP_SIZE_X 20
#define MAP_SIZE_Y 10
int map[MAP_SIZE_X][MAP_SIZE_Y];

/* 콘솔창 커서 위치 변경함수
 * windows.h 헤더 참조
 * parameter int x, int y (x,y좌표값)
*/
void setCursor(int x, int y){
	COORD pos = { x,y };//구조체 class
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	//_getch()_kbhit()
	//srand((unsigned)time(NULL)); //랜덤 시드설정
	//printf("%d\n", rand()); // 랜덤값 가져오기
	//#include <stdio.h>
	//#include <Windows.h>
	//#include <time.h>
	//#include <conio.h>
	//Sleep(1000);
}

int main(int argc, char* argv[])
{
	int snail_size = SNAIL_SIZE;
	if (argc > 1) {
		snail_size = atoi(argv[1]); // itoa
		printf("%d칸 사이즈로 생성합니다.\n\n", snail_size);
		for (int i = 0; i < argc; i++) {
			printf("%s\n", argv[i]);
		}
	}
	//이중포인터 동저할당
	int** snail = (int**)malloc(sizeof(int*) * snail_size);
	for (int i = 0; i < snail_size; i++) {
		snail[i] = (int*)malloc(sizeof(int) * snail_size);
	}
	int square_cnt = round((float)snail_size / 2);
	int array_counter = snail_size - 1;
	int input = 1;
	for (int i = 0; i < square_cnt; i++) { //square input
		for (int top = i; top < snail_size -i; top++) {
			snail[i][top] = input++;
		} // top line
		for (int right = i+1; right < snail_size -i; right++) {
			snail[right][array_counter - i] = input++;
		} // right line
		for (int bottom = snail_size -1-(i+1); bottom > (i-1); bottom--) {
			snail[array_counter - i][bottom] = input++;
		} // bottom line
		for (int left = (array_counter-1)-i; left > i; left--) {
			snail[left][i] = input++;
		} // left line
	}
	for (int i = 0; i < snail_size; i++) { //array output
		for (int j = 0; j < snail_size; j++) {
			printf("%d\t", snail[i][j]);
		}
		printf("\n\n");
	}
}