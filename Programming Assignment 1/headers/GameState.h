#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "Libraries.h"
#include "GameBank.h"

using namespace std;

class GameState {
private:
	GameBank leftBank;
	GameBank rightBank;

public:
    GameState();
	GameState(GameBank leftBank, GameBank rightBank);

	GameBank getLeftBank();
	void setLeftBank(GameBank leftBank);
	GameBank getRightBank();
	void setRightBank(GameBank rightBank);

	void print();
	bool isDefined();
	bool compareTo(GameState that);
	string getKey();
	int absoluteDifference(GameState that);
};

#endif