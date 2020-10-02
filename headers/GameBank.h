#ifndef GAME_BANK_H
#define GAME_BANK_H

#include "Libraries.h"

using namespace std;

class GameBank {
    public:
		int chickens;
		int wolves;
		int boat;

		GameBank();
        GameBank(int chickens, int wolves, int boat);

		bool isDefined();

};

#endif