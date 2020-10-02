#include "../headers/Libraries.h"
#include "../headers/FileUtils.h"
#include "../headers/SearchSolution.h"
#include "../headers/GameState.h"

using namespace std;

GameBank parseBank(string buffer);
GameState getInvalidState();

GameState readStateFile(string fileName)
{
	ifstream inFile(fileName);
	string buffer = "";
	GameBank rightBank, leftBank;

	if (inFile.is_open()) {

		if (getline(inFile, buffer) != 0) {
			leftBank = parseBank(buffer);
		}
		else {
			cout << "FILE ERROR: Could not read first line of a state file" << endl;
			if (inFile != 0) {
				inFile.close();
			}
			return getInvalidState();
		}

		buffer = "";

		if (getline(inFile, buffer) != 0) {
			rightBank = parseBank(buffer);
		}
		else {
			cout << "FILE ERROR: Could not read second line of a state file" << endl;
			if (inFile != 0) {
				inFile.close();
			}
			return  getInvalidState();
		}

	}
	else {
		cout << "FILE ERROR: Unable to open file" << endl;
		if (inFile != 0) {
			inFile.close();
		}
		return  getInvalidState();
	}

	if (inFile != 0) {
		inFile.close();
	}

	return GameState(leftBank, rightBank);
}

GameBank parseBank(string buffer) {
	int chickens = 0, wolves = 0, boat = 0;

	chickens = stoi(buffer.substr(0, buffer.find(",")));
	buffer.erase(0, buffer.find(",") + 1);

	wolves = stoi(buffer.substr(0, buffer.find(",")));
	buffer.erase(0, buffer.find(",") + 1);

	boat = stoi(buffer);

	return GameBank(chickens, wolves, boat);
}

GameState getInvalidState() {
	return GameState(GameBank(-1, -1, -1), GameBank(-1, -1, -1));
}

void outputSolutionToFile(SearchSolution solution, string fileName) {
	fstream outFile(fileName, ios::out);

	//redirect cout to file
	streambuf* stream_buffer_cout = cout.rdbuf();
	streambuf* stream_buffer_file = outFile.rdbuf();
	cout.rdbuf(stream_buffer_file);

	if (outFile.is_open()) {
		if (solution.expandedCount > 0) {
			cout << "Expanded Count: " << solution.expandedCount << endl;
		}
		else {
			cout << "No Solution" << endl;
		}

		for (GameState state : solution.solution) {
			state.print();
		}
	}

	//redirect back to screen
	cout.rdbuf(stream_buffer_cout);

	if (outFile != 0) {
		outFile.close();
	}
}