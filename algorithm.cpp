#include "algorithm.h"
#include <queue>
#include <vector>
#include <unordered_set>
#include <set>
#include <algorithm> // For heap functions
#include <chrono> // For measuring execution time
#include <ctime> // For std::clock

using namespace std;

struct Compare {
    bool operator()(Puzzle* lhs, Puzzle* rhs) {
        return lhs->getPathLength() > rhs->getPathLength();
    }
};
// Function to check if the puzzle is solvable
bool is_solvable(Puzzle* puzzle) {
    int inversions = 0;
    string board = puzzle->toString();
    for (int i = 0; i < 9; i++) {
        for (int j = i + 1; j < 9; j++) {
            if (board[i] != '0' && board[j] != '0' && board[i] > board[j]) {
                inversions++;
            }
        }
    }
    return inversions % 2 == 0;
}
///////////////////////////////////////////////////////////////////////////////////////////
//
// Search Algorithm:  UC with Strict Expanded List
//
// Move Generator:  
//
////////////////////////////////////////////////////////////////////////////////////////////
string uc_explist(string const initialState, string const goalState, int& pathLength, int &numOfStateExpansions, int& maxQLength,
                               float &actualRunningTime, int &numOfDeletionsFromMiddleOfHeap, int &numOfLocalLoopsAvoided, int &numOfAttemptedNodeReExpansions){
											 
    // Initialize the path string and start time
    string path;
    clock_t startTime = clock();

    // Initialize counters for statistics
    numOfStateExpansions = 0;
    maxQLength = 0;
    numOfDeletionsFromMiddleOfHeap = 0;
    numOfLocalLoopsAvoided = 0;
    numOfAttemptedNodeReExpansions = 0;

    // Print header for output
    cout << "------------------------------" << endl;
    cout << "<<uc_explist>>" << endl;
    cout << "------------------------------" << endl;


    // Priority queue to store nodes, sorted by path cost
    priority_queue<Puzzle*, vector<Puzzle*>, Compare> openList;

    // Unordered set to store closed nodes (nodes that have been expanded)
    unordered_set<string> closedList;

    // Create initial puzzle node and add it to the open list
    Puzzle* initialPuzzle = new Puzzle(initialState, goalState);
    openList.push(initialPuzzle);

    // Main loop of the search algorithm
    while (!openList.empty()) {
        // Get the node with the lowest path cost from the open list
        Puzzle* currentPuzzle = openList.top();
        openList.pop();

   if (currentPuzzle == nullptr) {
        cout << "currentPuzzle is null" << endl;
        continue;  // Skip this iteration if currentPuzzle is null
    }
        // If the node has already been expanded, skip it to avoid local loops
        if (closedList.find(currentPuzzle->toString()) != closedList.end()) {
            numOfLocalLoopsAvoided++;
            delete currentPuzzle;
            continue;
        }

        // Add the node to the closed list
        closedList.insert(currentPuzzle->toString());
        numOfStateExpansions++;

        // If the node is the goal node, set the path and path length and break the loop
        if (currentPuzzle->goalMatch()) {
            path = currentPuzzle->getPath();
            pathLength = currentPuzzle->getPathLength();
            delete currentPuzzle;
            break;
        }

        // Generate successors of the current node by moving the empty tile up, right, down, and left
        // Add each successor to the open list
        if (currentPuzzle->canMoveUp()) openList.push(currentPuzzle->moveUp());
        if (currentPuzzle->canMoveRight()) openList.push(currentPuzzle->moveRight());
        if (currentPuzzle->canMoveDown()) openList.push(currentPuzzle->moveDown());
        if (currentPuzzle->canMoveLeft()) openList.push(currentPuzzle->moveLeft());

        // Update the maximum length of the open list
        //maxQLength = max(maxQLength, (int)openList.size());
        maxQLength = (int)openList.size() > maxQLength ? (int)openList.size() : maxQLength;

        // Delete the current node to free up memory
        delete currentPuzzle;
    }

    // Calculate the actual running time of the search algorithm
    actualRunningTime = ((float)(clock() - startTime) / CLOCKS_PER_SEC);

        if (path.empty()) {
        cout << "No solution found." << endl;
    }


    return path;
}




///////////////////////////////////////////////////////////////////////////////////////////
//
// Search Algorithm:  A* with the Strict Expanded List
//
// Move Generator:  
//
////////////////////////////////////////////////////////////////////////////////////////////
string aStar_ExpandedList(string const initialState, string const goalState, int& pathLength, int &numOfStateExpansions, int& maxQLength,
                               float &actualRunningTime, int &numOfDeletionsFromMiddleOfHeap, int &numOfLocalLoopsAvoided, int &numOfAttemptedNodeReExpansions, heuristicFunction heuristic){
											 
   string path;
   clock_t startTime;
   
   numOfDeletionsFromMiddleOfHeap=0;
   numOfLocalLoopsAvoided=0;
   numOfAttemptedNodeReExpansions=0;


    // cout << "------------------------------" << endl;
    // cout << "<<aStar_ExpandedList>>" << endl;
    // cout << "------------------------------" << endl;
	actualRunningTime=0.0;	
	startTime = clock();
	srand(time(NULL)); //RANDOM NUMBER GENERATOR - ONLY FOR THIS DEMO.  YOU REALLY DON'T NEED THIS! DISABLE THIS STATEMENT.
	maxQLength= rand() % 200; //AT THE MOMENT, THIS IS JUST GENERATING SOME DUMMY VALUE.  YOUR ALGORITHM IMPLEMENTATION SHOULD COMPUTE THIS PROPERLY.
	numOfStateExpansions = rand() % 200; //AT THE MOMENT, THIS IS JUST GENERATING SOME DUMMY VALUE.  YOUR ALGORITHM IMPLEMENTATION SHOULD COMPUTE THIS PROPERLY


	
	
//***********************************************************************************************************
	actualRunningTime = ((float)(clock() - startTime)/CLOCKS_PER_SEC);
	path = "DDRRLLLUUURDLUDURDLUU"; //this is just a dummy path for testing the function
	pathLength = path.size();
	return path;		
		
}

