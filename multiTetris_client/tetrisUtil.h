#pragma once
#define _WINSOCKAPI_
#include <iostream>
#include <Windows.h>
#include <time.h>
#include <conio.h>
#include <thread>

#include "mapData.h"
#include "block.h"
#include "gameSettings.h"



void setCursor(int x, int y) {
	COORD pos = { x,y };//±¸Á¶Ã¼ class
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void CursorView(char show)
{
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;

	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}