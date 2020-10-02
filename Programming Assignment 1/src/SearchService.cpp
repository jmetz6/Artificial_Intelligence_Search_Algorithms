#include "../headers/Libraries.h"
#include "../headers/SearchService.h"
#include "../headers/SearchSolution.h"

using namespace std;

Action ACTIONS[] = {
	ACTION_ONE_CHICKEN,
	ACTION_TWO_CHICKENS,
	ACTION_ONE_WOLF,
	ACTION_ONE_WOLF_ONE_CHICKEN,
	ACTION_TWO_WOLVES
};

Node NODE_NULL = { state: GameState(), parent: 0, action : ACTION_NONE, pathCost : -100 };
Node NODE_CUTOFF = { state: GameState(), parent: 0, action : ACTION_NONE, pathCost : -500 };

GameState createState(GameBank left, GameBank right, Action action);
GameState OneChicken(GameBank left, GameBank right);
GameState TwoChicken(GameBank left, GameBank right);
GameState OneWolf(GameBank left, GameBank right);
GameState OneWolfOneChicken(GameBank left, GameBank right);
GameState TwoWolves(GameBank left, GameBank right);
Node* AStarExpand(Node* node, GameState goal, map<string, Node*>& explored, map<string, Node*>& frontier, vector<Node*>& nodes, priority_queue<Node*, vector<Node*>, AStarNodeComparator>& orderedNodes);
Node* Expand(Node* node, GameState goal, map<string, Node*>& explored, map<string, Node*>& frontier, list<string*>& frontierKeyLookup);
Node* ChildNode(Node* parent, Action action);
Node* RecursiveDLS(Node* node, GameState initial, GameState goal, map<string, Node*>& explored, int& expandedCount, vector<Node*>& nodes, int depthLimit);
Node* DepthLimitedSearch(GameState initial, GameState goal, map<string, Node*>& explored, int& expandedCount, vector<Node*>& nodes, int depthLimit);
bool isNodePresentInList(map<string, Node*>& nodeList, Node* node);
bool isActionLegal(GameState state, Action action);
bool compareNodes(Node left, Node right);
int stepCost(GameState parentState, Action action);
int heuristic(GameState state, GameState goal, int pathCost);
string toStringAction(Action action);
void printNodeList(map<string, Node*>& nodes);
void freeMap(map<string, Node*>& nodes);
void freeList(list<string*>& strings);

SearchService::SearchService() {}

SearchSolution SearchService::search(GameState initial, GameState goal, SearchMode mode)
{
	if (!initial.isDefined() || !goal.isDefined()) {
		return SearchSolution();
	}

	SearchSolution solution = SearchSolution();
	map<string, Node*>* frontier = new map<string, Node*>();
	map<string, Node*>* explored = new map<string, Node*>();
	vector<Node*> nodes = vector<Node*>();
	int expandedCount = 0;
	Node* answer; 

	switch (mode) {
		case BFS: answer = BreadthFirstSearch(initial, goal, *explored, *frontier, expandedCount);
			break;
		case DFS: answer = DepthFirstSearch(initial, goal, *explored, *frontier, expandedCount);
			break;
		case IDDFS: answer = IterativeDeepeningDepthFirstSearch(initial, goal, *explored, nodes, expandedCount);
			break;
		case ASTAR: answer = AStar(initial, goal, *explored, *frontier, nodes, expandedCount);
			break;
		default: *answer = NODE_NULL;
			break;
	}
	
	if (!compareNodes(*answer, NODE_NULL)) {
		Node* n = answer;
		while (n != 0) {
			solution.solution.push_front(n->state);
			n = n->parent;
		}
		solution.expandedCount = expandedCount;
		solution.pathCost = answer->pathCost;
	}

	if (mode == BFS || mode == DFS) {
		freeMap(*frontier);
		freeMap(*explored);

		if (answer != 0) {
			delete answer;
			answer = 0;
		}
	}
	else if(mode == IDDFS || mode == ASTAR) {
		for (Node* n : nodes) {
			if (n != 0) {
				delete n;
			}
		}
		delete frontier;
		delete explored;
	}




	return solution;
}

Node* SearchService::BreadthFirstSearch(GameState initial, GameState goal, map<string, Node*>& explored, map<string, Node*>& frontier, int& expandedCount)
{
	Node* a = new Node();
	a->state = initial; 
	a->parent = 0;
	a->action = ACTION_NONE;
	a->pathCost = 0;

	expandedCount = 0;

	if (a->state.compareTo(goal)) {
		return a;
	}
	
	list<string*>* frontierKeyLookup = new list<string*>();
	frontierKeyLookup->push_back(new string(a->state.getKey()));
	frontier[a->state.getKey()] = a;

	while(true) {
		if (frontier.empty()) {
			freeList(*frontierKeyLookup);
			return new Node(NODE_NULL);
		}

		Node* n = frontier[*(frontierKeyLookup->front())];
		explored[*(frontierKeyLookup->front())] = n;

		frontier[*(frontierKeyLookup->front())] = 0;
		frontier.erase(*(frontierKeyLookup->front()));
		delete frontierKeyLookup->front();
		frontierKeyLookup->pop_front();

		expandedCount++;
		Node* potentialSolution = Expand(n, goal, explored, frontier, *frontierKeyLookup);

		if (!compareNodes(*potentialSolution, NODE_NULL)) {
			freeList(*frontierKeyLookup);
			return potentialSolution;
		}

		if (potentialSolution != 0) {
			delete potentialSolution;
			potentialSolution = 0;
		}
	}
	freeList(*frontierKeyLookup);
}

Node* SearchService::DepthFirstSearch(GameState initial, GameState goal, map<string, Node*>& explored, map<string, Node*>& frontier, int& expandedCount)
{
	Node* a = new Node();
	a->state = initial;
	a->parent = 0;
	a->action = ACTION_NONE;
	a->pathCost = 0;

	expandedCount = 0;

	if (a->state.compareTo(goal)) {
		return a;
	}

	list<string*>* frontierKeyLookup = new list<string*>();
	frontierKeyLookup->push_back(new string(a->state.getKey()));
	frontier[a->state.getKey()] = a;

	while (true) {
		if (frontier.empty()) {
			freeList(*frontierKeyLookup);
			return new Node(NODE_NULL);
		}

		Node* n = frontier[*(frontierKeyLookup->back())];
		explored[*(frontierKeyLookup->back())] = n;

		frontier[*(frontierKeyLookup->back())] = 0;
		frontier.erase(*(frontierKeyLookup->back()));
		delete frontierKeyLookup->back();
		frontierKeyLookup->pop_back();

		expandedCount++;
		Node* potentialSolution = Expand(n, goal, explored, frontier, *frontierKeyLookup);

		if (!compareNodes(*potentialSolution, NODE_NULL)) {
			freeList(*frontierKeyLookup);
			return potentialSolution;
		}

		if (potentialSolution != 0) {
			delete potentialSolution;
			potentialSolution = 0;
		}
	}
	freeList(*frontierKeyLookup);
}

Node* SearchService::AStar(GameState initial, GameState goal, map<string, Node*>& explored, map<string, Node*>& frontier, vector<Node*>& nodes, int& expandedCount)
{
	Node* root = new Node();
	root->action = ACTION_NONE;
	root->parent = 0;
	root->pathCost = 0;
	root->state = initial;
	root->heuristic = 0;

	priority_queue<Node*, vector<Node*>, AStarNodeComparator> orderedNodes = priority_queue<Node*, vector<Node*>, AStarNodeComparator>();

	nodes.push_back(root);
	frontier[initial.getKey()] = root;
	orderedNodes.push(root);

	while (true) {
		if (frontier.empty()) {
			Node* n = new Node(NODE_NULL);
			nodes.push_back(n);
			return n;
		}

		Node* node = orderedNodes.top();
		orderedNodes.pop();
		if(node->state.compareTo(goal)) { 
			return node;
		}

		//add leaf to explored list
		expandedCount++;
		explored[node->state.getKey()] = node;
		frontier.erase(node->state.getKey());

		//expand the node; add nodes to frontier if not in frontier or explored
		Node* result = AStarExpand(node, goal, explored, frontier, nodes, orderedNodes);
		if (result->state.compareTo(goal)) {
			return result;
		}
	}

}

Node* AStarExpand(Node* node, GameState goal, map<string, Node*>& explored, map<string, Node*>& frontier, vector<Node*>& nodes, priority_queue<Node*, vector<Node*>, AStarNodeComparator>& orderedNodes) {
	//creates map of child nodes
	for (Action action : ACTIONS) {
		Node* child;

		bool isLegal = isActionLegal(node->state, action);
		if (isLegal) {
			child = ChildNode(node, action);
			
			if (!isNodePresentInList(explored, child) && !isNodePresentInList(frontier, child)) {
				nodes.push_back(child);
				if (child->state.compareTo(goal)) {
					return child;
				}
				child->heuristic = heuristic(child->state, goal, child->pathCost);
				//cout << child->heuristic << endl; //testing
				frontier[child->state.getKey()] = child;
				orderedNodes.push(child);
			}
			else {
				delete child;
				child = 0;
			}
		}
	}
	Node* n = new Node(NODE_NULL);;
	nodes.push_back(n);
	return n;
}

int heuristic(GameState state, GameState goal, int pathCost) {
	int hn = pathCost;
	hn += state.absoluteDifference(goal);
	return hn;
}

Node* SearchService::IterativeDeepeningDepthFirstSearch(GameState initial, GameState goal, map<string, Node*>& explored, vector<Node*>& nodes, int& expandedCount)
{
	int depthLimit = 0;
	
	while (true) {
		Node* result = DepthLimitedSearch(initial, goal, explored, expandedCount, nodes, depthLimit);
		if (compareNodes(*result, NODE_CUTOFF)) {
			explored.clear();

			depthLimit++;
		}
		else {
			return result;
		}
		
	}
}

Node* DepthLimitedSearch(GameState initial, GameState goal, map<string, Node*>& explored, int& expandedCount, vector<Node*>& nodes, int depthLimit) {
	Node* root = new Node();
	root->action = ACTION_NONE;
	root->parent = 0;
	root->pathCost = 0;
	root->state = initial;

	nodes.push_back(root);

	Node* result = RecursiveDLS(root, initial, goal, explored, expandedCount, nodes, depthLimit);

	return result;
}

Node* RecursiveDLS(Node* node, GameState initial, GameState goal, map<string, Node*>& explored, int& expandedCount, vector<Node*>& nodes, int depthLimit) {
	if (node->state.compareTo(goal)) {
		return node;
	}
	else if (depthLimit == 0) {
		Node* n = new Node(NODE_CUTOFF);
		nodes.push_back(n);
		return n;
	}
	else {
		//Explore the node
		explored[node->state.getKey()] = node;
		expandedCount++;

		bool cutoffOccurred = false;
		//For Each child explore until depth limit
		for (Action action : ACTIONS) {
			if (!isActionLegal(node->state, action)) {
				continue;
			}

			Node* child = ChildNode(node, action);	
			if (isNodePresentInList(explored, child)) {
				//Child is a duplicate state
				if (child != 0) {
					delete child;
					child = 0;
				}
				continue;
			}

			nodes.push_back(child);

			Node* result = RecursiveDLS(child, initial, goal, explored, expandedCount, nodes, (depthLimit - 1));
			if (compareNodes(*result, NODE_CUTOFF)) {
				cutoffOccurred = true;
			}
			else if (!compareNodes(*result, NODE_NULL)) { //if not failure or cutoff then return solution
				return result;
			}
		}
		if (cutoffOccurred) {
			Node* n = new Node(NODE_CUTOFF);
			nodes.push_back(n);
			return n;
		}
		else {
			Node* n = new Node(NODE_NULL);
			nodes.push_back(n);
			return n;
		}
	}
}

//returns map of successors
Node* Expand(Node* node, GameState goal, map<string, Node*>& explored, map<string, Node*>& frontier, list<string*>& frontierKeyLookup)
{
	//creates map of child nodes
	for (Action action : ACTIONS) {
		Node* child;

		bool isLegal = isActionLegal(node->state, action); 
		if (isLegal) {
			child = ChildNode(node, action);

			if (!isNodePresentInList(explored, child) && !isNodePresentInList(frontier, child)) {
				if (child->state.compareTo(goal)) {
					return child;
				}
				frontierKeyLookup.push_back(new string(child->state.getKey()));
				frontier[child->state.getKey()] = child;
			}
			else {
				delete child;
				child = 0;
			}
		}	
	}
	return new Node(NODE_NULL);
}

bool isActionLegal(GameState state, Action action) {
	GameState newState = createState(state.getLeftBank(), state.getRightBank(), action);
	GameBank leftBank = newState.getLeftBank();
	GameBank rightBank = newState.getRightBank();
	if (!leftBank.isDefined() || !rightBank.isDefined() || (leftBank.wolves > leftBank.chickens && leftBank.chickens != 0) || (rightBank.wolves > rightBank.chickens && rightBank.chickens != 0)) {
		return false;
	}
	return true;
}

//gets the child node for a specified node and action
Node* ChildNode(Node* parent, Action action) 
{
	Node* n = new Node();
	n->action = action;
	n->parent = parent;
	n->state = createState(parent->state.getLeftBank(), parent->state.getRightBank(), action);
	n->pathCost = parent->pathCost + stepCost(parent->state, action);
	return n;
}

GameState createState(GameBank left, GameBank right, Action action) {
	switch (action) {
		case ACTION_ONE_CHICKEN: return OneChicken(left, right);
			break;
		case ACTION_TWO_CHICKENS: return TwoChicken(left, right);
			break;
		case ACTION_ONE_WOLF: return OneWolf(left, right);
			break;
		case ACTION_ONE_WOLF_ONE_CHICKEN: return OneWolfOneChicken(left, right);
			break;
		case ACTION_TWO_WOLVES: return TwoWolves(left, right);
			break;
		default: return GameState(left, right);
			break;
	}
}

GameState OneChicken(GameBank left, GameBank right) {
	if (left.boat == 1) {
		left.chickens--;
		left.boat = 0;
		right.chickens++;
		right.boat = 1;
	}
	else {
		right.chickens--;
		right.boat = 0;
		left.chickens++;
		left.boat = 1;
	}
	return GameState(left, right);
}

GameState TwoChicken(GameBank left, GameBank right) {
	if (left.boat == 1) {
		left.chickens -= 2;
		left.boat = 0;
		right.chickens += 2;
		right.boat = 1;
	}
	else {
		right.chickens -= 2;
		right.boat = 0;
		left.chickens += 2;
		left.boat = 1;
	}
	return GameState(left, right);
}

GameState OneWolf(GameBank left, GameBank right) {
	if (left.boat == 1) {
		left.wolves--;
		left.boat = 0;
		right.wolves++;
		right.boat = 1;
	}
	else {
		right.wolves--;
		right.boat = 0;
		left.wolves++;
		left.boat = 1;
	}
	return GameState(left, right);
}

GameState OneWolfOneChicken(GameBank left, GameBank right) {
	if (left.boat == 1) {
		left.wolves--;
		left.chickens--;
		left.boat = 0;
		right.wolves++;
		right.chickens++;
		right.boat = 1;
	}
	else {
		right.wolves--;
		right.chickens--;
		right.boat = 0;
		left.wolves++;
		left.chickens++;
		left.boat = 1;
	}
	return GameState(left, right);
}

GameState TwoWolves(GameBank left, GameBank right) {
	if (left.boat == 1) {
		left.wolves -= 2;
		left.boat = 0;
		right.wolves += 2;
		right.boat = 1;
	}
	else {
		right.wolves -= 2;
		right.boat = 0;
		left.wolves += 2;
		left.boat = 1;
	}
	return GameState(left, right);
}

int stepCost(GameState parentState, Action action) {
	//TODO
	return 1;
}

bool isNodePresentInList(map<string, Node*>& nodeList, Node* node) {
	if (nodeList.count(node->state.getKey()) > 0) {
		return true;
	}
	return false;
}

bool compareNodes(Node left, Node right) {
	if (left.action != right.action) {
		return false;
	}

	if (left.parent != right.parent) {
		return false;
	}

	if (left.pathCost != right.pathCost) {
		return false;
	}

	if (!left.state.compareTo(right.state)) {
		return false;
	}

	return true;
}

string toStringAction(Action action) {
	switch (action) {
	case ACTION_ONE_CHICKEN: return "One Chicken";
		break;
	case ACTION_TWO_CHICKENS: return "Two Chicken";
		break;
	case ACTION_ONE_WOLF: return "One Wolf";
		break;
	case ACTION_ONE_WOLF_ONE_CHICKEN: return "One Wolf One Chicken";
		break;
	case ACTION_TWO_WOLVES: return "Two Wolves";
		break;
	default: return "None";
		break;
	}
}

void printNodeList(map<string, Node*>& nodes) {
	map<string, Node*>::iterator it = nodes.begin();
	for (it = nodes.begin(); it != nodes.end(); it++) {
		(*it).second->state.print();
	}
}

void freeMap(map<string, Node*>& nodes) {
	map<string, Node*>::iterator it = nodes.begin();
	for (it = nodes.begin(); it != nodes.end(); it++) {
		if (nodes.count((*it).first) > 0) {
			if (nodes[(*it).first] != 0) {
				delete nodes[(*it).first];
				nodes[(*it).first] = 0;
			}
		}
	}
	delete &nodes;
}

void freeList(list<string*>& strings) {
	for (string* s : strings) {
		if (s != 0) {
			delete s;
			s = 0;
		}
	}
	delete &strings;
}