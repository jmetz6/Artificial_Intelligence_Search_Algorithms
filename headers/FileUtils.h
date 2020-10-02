#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include "Libraries.h"
#include "GameState.h"
#include "SearchSolution.h"

using namespace std;

GameState readStateFile(string fileName);
void outputSolutionToFile(SearchSolution solution, string fileName);

#endif