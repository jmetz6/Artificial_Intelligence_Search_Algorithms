#include "../headers/Libraries.h"
#include "../headers/SearchSolution.h"

using namespace std;

SearchSolution::SearchSolution() {
	pathCost = 0;
	expandedCount = 0;
	solution = list<GameState>();
}

SearchSolution::SearchSolution(int pathCost, int expandedCount, list<GameState> solution)
{
	this->pathCost = pathCost;
	this->expandedCount = expandedCount;
	this->solution = solution;
}
