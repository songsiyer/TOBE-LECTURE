#include "gameSettings.h"

gameSettings::gameSettings()
{
	gameLevel = 1;
	score = 0;
}

gameSettings::~gameSettings()
{
}

void gameSettings::initial()
{
	gameLevel = 1;
	score = 0;
}

void gameSettings::levelUp()
{
	gameLevel++;
}

void gameSettings::scoreUp(int completeLines)
{
	switch (completeLines-1)
	{
	case 1: score += 100; break;
	case 2: score += 300; break;
	case 3: score += 700; break;
	case 4: score += 1500; break;
	default:
		break;
	}
	if (score / 10000 > gameLevel) {
		gameLevel++;
	}
}
