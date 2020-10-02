#ifndef SEARCH_SOLUTION_H
#define SEARCH_SOLUTION_H

#include "Libraries.h"
#include "GameState.h"

using namespace std;

class SearchSolution {
	public:
		SearchSolution();
		SearchSolution(int pathCost, int expandedCount, list<GameState> solution);

		int pathCost;
		int expandedCount;
		list<GameState> solution;

};

#endif // !SEARCH_SOLUTION_H
