#include "../headers/Libraries.h"
#include "../headers/GameBank.h"
#include "../headers/GameState.h"
#include "../headers/SearchService.h"
#include "../headers/SearchSolution.h"
#include "../headers/FileUtils.h"

using namespace std;

void handleArguments(char** args, string* initialStateFileName, string* goalStateFileName, SearchMode* mode, string* outputFileName);
SearchMode parseMode(string mode);

int main(int argc, char** argv) {
	//initial state file; goal state file; mode; output file
	if (argc < 5) {
		cout << "ERROR: Too few arguments" << endl;
		cout << "Game.exe: initial state file; goal state file; mode; output file;" << endl;
		return -1;
	}

	string initialStateFileName;
	string goalStateFileName;
	SearchMode mode;
	string outputFileName;
	handleArguments(argv, &initialStateFileName, &goalStateFileName, &mode, &outputFileName);

	if (mode == INVALID) {
		cout << "ERROR: Invalid search mode" << endl;
		cout << "Enter bfs, dfs, iddfs, or astar" << endl;
		return -1;
	}

	//Read the initial state file and the goal state file
	GameState initialState = readStateFile(initialStateFileName);
	GameState goalState = readStateFile(goalStateFileName);

	//initialState.print();
	//goalState.print();

	SearchService searchService = SearchService();
	
	SearchSolution solution = searchService.search(initialState, goalState, mode);

	if (solution.solution.size() > 0) {
		cout << "Nodes Count: " << solution.solution.size() << endl;
		cout << "Expanded Count: " << solution.expandedCount << endl;
		for (GameState s : solution.solution) {
			s.print();
		}
	}
	else {
		cout << "No Solution" << endl;
	}

	outputSolutionToFile(solution, outputFileName);

	return 0;
}

void handleArguments(char** args, string* initialStateFileName, string* goalStateFileName, SearchMode* mode, string* outputFileName) {
	*initialStateFileName = string(args[1]);
	*goalStateFileName = string(args[2]);
	*mode = parseMode(string(args[3]));
	*outputFileName = string(args[4]);
}

SearchMode parseMode(string mode) {
	if ((mode.compare("bfs")) == 0) {
		return BFS;
	}
	else if ((mode.compare("dfs")) == 0) {
		return DFS;
	}
	else if ((mode.compare("iddfs")) == 0) {
		return IDDFS;
	}
	else if ((mode.compare("astar")) == 0) {
		return ASTAR;
	}
	else {
		return INVALID;
	}
}