#pragma once
#define BASE_SPEED 500
class gameSettings
{
private:
	int gameSpeed;
	int gameLevel;
	int score;

public:
	gameSettings();
	~gameSettings();
	void initial();
	void levelUp();
	void scoreUp(int completeLines);


	int getGameSpeed() {
		return BASE_SPEED - (gameLevel-1)*50;
	}
	void setGameLevel(int gameLevel) {
		this->gameLevel = gameLevel;
	}
	int getGameLevel() {
		return gameLevel;
	}
	void setScore(int score) {
		this->score = score;
	}
	int getScore() {
		return score;
	}
};

