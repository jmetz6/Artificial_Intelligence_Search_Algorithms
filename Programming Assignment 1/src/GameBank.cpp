#include "../headers/Libraries.h"
#include "../headers/GameBank.h"

using namespace std;

GameBank::GameBank(int chickens, int wolves, int boat) {
	this->chickens = chickens;
	this->wolves = wolves;
	this->boat = boat;
}

GameBank::GameBank() {
	this->chickens = 0;
	this->wolves = 0;
	this->boat = 0;
}

bool GameBank::isDefined() {
	if (this->chickens > -1 && this->wolves > -1 && this->boat > -1) {
		return true;
	}
	return false;
}
