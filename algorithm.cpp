#include "algorithm.h"
#include <queue>
#include <vector>
#include <unordered_set>
#include <set>
#include <algorithm> // For heap functions
#include <chrono>    // For measuring execution time
#include <ctime>     // For std::clock

using namespace std;

struct Compare
{
    bool operator()(const Puzzle *lhs, const Puzzle *rhs) const
    {
        return lhs->getFCost() > rhs->getFCost();
    }
};

struct CompareUC
{
    bool operator()(const Puzzle *lhs, const Puzzle *rhs) const
    {
        return lhs->getPathLength() > rhs->getPathLength();
    }
};
// Function to check if the puzzle is solvable
bool is_solvable(Puzzle *puzzle)
{
    int inversions = 0;
    string board = puzzle->toString();
    for (int i = 0; i < 9; i++)
    {
        for (int j = i + 1; j < 9; j++)
        {
            if (board[i] != '0' && board[j] != '0' && board[i] > board[j])
            {
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
string uc_explist(string const initialState, string const goalState, int &pathLength, int &numOfStateExpansions, int &maxQLength,
                  float &actualRunningTime, int &numOfDeletionsFromMiddleOfHeap, int &numOfLocalLoopsAvoided, int &numOfAttemptedNodeReExpansions)
{

    // Initialize the path string and start time
    string path = "";
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
    priority_queue<Puzzle *, vector<Puzzle *>, CompareUC> openList;

    // Unordered set to store closed nodes (nodes that have been expanded)
    unordered_set<string> closedList;

    // Create initial puzzle node and add it to the open list
    Puzzle *initialPuzzle = new Puzzle(initialState, goalState);
    openList.push(initialPuzzle);

    if (!is_solvable(initialPuzzle))
    {
        cout << "No solution found." << endl;
        return path;
    }

    // Main loop of the search algorithm
    while (!openList.empty())
    {
        // Get the node with the lowest path cost from the open list
        Puzzle *currentPuzzle = openList.top();
        openList.pop();

        // If the node has already been expanded, skip it to avoid local loops
        if (closedList.find(currentPuzzle->toString()) != closedList.end())
        {
            numOfLocalLoopsAvoided++;
            delete currentPuzzle;
            continue;
        }

        // Add the node to the closed list
        closedList.insert(currentPuzzle->toString());
        numOfStateExpansions++;

        // If the node is the goal node, set the path and path length and break the loop
        if (currentPuzzle->goalMatch())
        {
            path = currentPuzzle->getPath();
            cout << "Path: " << path << endl;
            pathLength = currentPuzzle->getPathLength();
            delete currentPuzzle;
            break;
        }

        // Generate successors of the current node by moving the empty tile up, right, down, and left
        // Add each successor to the open list
        if (currentPuzzle->canMoveUp())
            openList.push(currentPuzzle->moveUp());
        if (currentPuzzle->canMoveRight())
            openList.push(currentPuzzle->moveRight());
        if (currentPuzzle->canMoveDown())
            openList.push(currentPuzzle->moveDown());
        if (currentPuzzle->canMoveLeft())
            openList.push(currentPuzzle->moveLeft());

        // Update the maximum length of the open list
        // maxQLength = max(maxQLength, (int)openList.size());
        maxQLength = (int)openList.size() > maxQLength ? (int)openList.size() : maxQLength;

        // Delete the current node to free up memory
        delete currentPuzzle;
    }

    // Calculate the actual running time of the search algorithm
    actualRunningTime = ((float)(clock() - startTime) / CLOCKS_PER_SEC);

    if (path.empty())
    {
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
string aStar_ExpandedList(string const initialState, string const goalState, int &pathLength, int &numOfStateExpansions, int &maxQLength,
                          float &actualRunningTime, int &numOfDeletionsFromMiddleOfHeap, int &numOfLocalLoopsAvoided, int &numOfAttemptedNodeReExpansions, heuristicFunction heuristic)
{
    // Initialize the path string and start time
    string path = "";
    clock_t startTime = clock();

    // Initialize counters
    numOfStateExpansions = 0;
    maxQLength = 0;
    numOfDeletionsFromMiddleOfHeap = 0;
    numOfLocalLoopsAvoided = 0;
    numOfAttemptedNodeReExpansions = 0;

    // Print header for output
    cout << "------------------------------" << endl;
    cout << "<<aStar_ExpandedList>>" << endl;
    cout << "------------------------------" << endl;

    // Create priority queue (open list) and closed list
    priority_queue<Puzzle *, vector<Puzzle *>, Compare> openList;
    unordered_set<string> closedList;

    // Create initial puzzle and add to open list
    Puzzle *initialPuzzle = new Puzzle(initialState, goalState);
    openList.push(initialPuzzle);

    while (!openList.empty())
    {
        // Get the puzzle with the lowest f-cost
        Puzzle *currentPuzzle = openList.top();
        openList.pop();

        // Check if we've reached the goal state
        if (currentPuzzle->goalMatch())
        {
            path = currentPuzzle->getPath();
            pathLength = currentPuzzle->getPathLength();
            actualRunningTime = ((float)(clock() - startTime) / CLOCKS_PER_SEC);
            delete currentPuzzle;
            return path;
        }

        // Check if the current state has already been expanded
        if (closedList.find(currentPuzzle->toString()) != closedList.end())
        {
            numOfAttemptedNodeReExpansions++;
            delete currentPuzzle;
            continue;
        }

        // Expand the current state
        numOfStateExpansions++;
        closedList.insert(currentPuzzle->toString());

        // Generate successors
        vector<Puzzle *> successors;
        if (currentPuzzle->canMoveUp())
            successors.push_back(currentPuzzle->moveUp());
        if (currentPuzzle->canMoveRight())
            successors.push_back(currentPuzzle->moveRight());
        if (currentPuzzle->canMoveDown())
            successors.push_back(currentPuzzle->moveDown());
        if (currentPuzzle->canMoveLeft())
            successors.push_back(currentPuzzle->moveLeft());

        // Process successors
        for (Puzzle *successor : successors)
        {
            if (closedList.find(successor->toString()) == closedList.end())
            {
                // Update heuristic cost and f-cost
                successor->updateHCost(heuristic);
                successor->updateFCost();
                openList.push(successor);
            }
            else
            {
                numOfLocalLoopsAvoided++;
                delete successor;
            }
        }

        // Update maximum queue length
        maxQLength = max(maxQLength, (int)openList.size());

        delete currentPuzzle;
    }

    // If we've exhausted the open list without finding a solution
    actualRunningTime = ((float)(clock() - startTime) / CLOCKS_PER_SEC);
    return "";
}
