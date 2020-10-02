#ifndef SEARCH_SERVICE_H
#define SEARCH_SERVICE_H

#include "Libraries.h"
#include "GameState.h"
#include "SearchSolution.h"

using namespace std;

enum SearchMode { INVALID, BFS, DFS, IDDFS, ASTAR };
enum Action { ACTION_NONE, ACTION_ONE_CHICKEN, ACTION_TWO_CHICKENS, ACTION_ONE_WOLF, ACTION_ONE_WOLF_ONE_CHICKEN, ACTION_TWO_WOLVES };

typedef struct Node {
	GameState state;
	Node* parent;
	Action action;
	int pathCost;
	int heuristic;
} Node;

class SearchService {
    public:
        SearchService();
		static SearchSolution search(GameState initial, GameState goal, SearchMode mode);
        static Node* BreadthFirstSearch(GameState initial, GameState goal, map<string, Node*>& explored, map<string, Node*>& frontier, int& expandedCount);
		static Node* DepthFirstSearch(GameState initial, GameState goal, map<string, Node*>& explored, map<string, Node*>& frontier, int& expandedCount);
		static Node* IterativeDeepeningDepthFirstSearch(GameState initial, GameState goal, map<string, Node*>& explored, vector<Node*>& nodes, int& expandedCount);
		static Node* AStar(GameState initial, GameState goal, map<string, Node*>& explored, map<string, Node*>& frontier, vector<Node*>& nodes, int& expandedCount);
};

class AStarNodeComparator {
	public:
		int operator() (const Node* n1, const Node* n2) {
			return n1->heuristic > n2->heuristic;
		}
};

#endif