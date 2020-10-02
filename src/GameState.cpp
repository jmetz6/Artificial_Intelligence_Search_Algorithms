#include "../headers/Libraries.h"
#include "../headers/GameState.h"

using namespace std;

GameState::GameState() {
}

GameState::GameState(GameBank leftBank, GameBank rightBank)
{
	this->leftBank = leftBank;
	this->rightBank = rightBank;
}

GameBank GameState::getLeftBank()
{
	return this->leftBank;
}

void GameState::setLeftBank(GameBank leftBank)
{
	this->leftBank = leftBank;
}

GameBank GameState::getRightBank()
{
	return this->rightBank;
}

void GameState::setRightBank(GameBank rightBank)
{
	this->rightBank = rightBank;
}

void GameState::print() {
	if (this->leftBank.isDefined() && this->rightBank.isDefined()) {
		cout << "Left Bank: " << " chickens: " << this->leftBank.chickens << ", wolves: " << this->leftBank.wolves << ", boat: " << this->leftBank.boat << endl;
		cout << "Right Bank: " << " chickens: " << this->rightBank.chickens << ", wolves: " << this->rightBank.wolves << ", boat: " << this->rightBank.boat << endl;
	}
	
}

bool GameState::isDefined()
{
	if (this->leftBank.isDefined() && this->rightBank.isDefined()) {
		return true;
	}
	return false;
}

bool GameState::compareTo(GameState that)
{
	if (this->leftBank.chickens != that.leftBank.chickens) {
		return false;
	}
	if (this->leftBank.wolves != that.leftBank.wolves) {
		return false;
	}
	if (this->leftBank.boat != that.leftBank.boat) {
		return false;
	}

	if (this->rightBank.chickens != that.rightBank.chickens) {
		return false;
	}
	if (this->rightBank.wolves != that.rightBank.wolves) {
		return false;
	}
	if (this->rightBank.boat != that.rightBank.boat) {
		return false;
	}

	return true;
}

string GameState::getKey()
{
	if (this->isDefined()) {
		string key;
		GameBank leftBank = this->getLeftBank();
		GameBank rightBank = this->getRightBank();
		key = "left_" 
			+ to_string(leftBank.chickens) + "_" 
			+ to_string(leftBank.wolves) + "_" 
			+ to_string(leftBank.boat) + "_" 
			+ "right_" 
			+ to_string(rightBank.chickens) + "_" 
			+ to_string(rightBank.wolves) 
			+ "_" + to_string(rightBank.boat);
		return key;
	}
	return "";
}

int GameState::absoluteDifference(GameState that)
{
	int dif = 0;
	dif += abs(this->getLeftBank().chickens - that.getLeftBank().chickens);
	dif += abs(this->getLeftBank().wolves - that.getLeftBank().wolves);
	dif += abs(this->getLeftBank().boat - that.getLeftBank().boat);

	dif += abs(this->getRightBank().chickens - that.getRightBank().chickens);
	dif += abs(this->getRightBank().wolves - that.getRightBank().wolves);
	dif += abs(this->getRightBank().boat - that.getRightBank().boat);
	return dif;
}
