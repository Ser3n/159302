#include "puzzle.h"
#include <cmath>
#include <string>
#include <assert.h>

using namespace std;

//////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////
Puzzle::Puzzle(const Puzzle &p) : path(p.path)
{

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = p.board[i][j];
            goalBoard[i][j] = p.goalBoard[i][j];
        }
    }

    x0 = p.x0;
    y0 = p.y0;
    // path = p.path;
    pathLength = p.pathLength;
    hCost = p.hCost;
    fCost = p.fCost;
    strBoard = toString(); // uses the board contents to generate the string equivalent
    depth = p.depth;
}

//////////////////////////////////////////////////////////////
// constructor
// inputs:  initial state, goal state
//////////////////////////////////////////////////////////////
Puzzle::Puzzle(string const elements, string const goal)
{

    int n;

    n = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = elements[n] - '0';
            if (board[i][j] == 0)
            {
                x0 = j;
                y0 = i;
            }
            n++;
        }
    }

    ///////////////////////
    n = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            goalBoard[i][j] = goal[n] - '0';
            n++;
        }
    }
    ///////////////////////
    path = "";
    pathLength = 0;
    hCost = 0;
    fCost = 0;
    depth = 0;
    strBoard = toString();
}

void Puzzle::setDepth(int d)
{
    depth = d;
}

int Puzzle::getDepth()
{
    return depth;
}

void Puzzle::updateHCost(heuristicFunction hFunction)
{
    hCost = h(hFunction);
}

void Puzzle::updateFCost()
{
    // A*
    fCost = pathLength + hCost;
}

int Puzzle::getFCost() const
{
    return fCost;
}

int Puzzle::getHCost() const
{
    return hCost;
}

int Puzzle::getGCost() const
{
    return pathLength;
}

// Heuristic function implementation
int Puzzle::h(heuristicFunction hFunction) const
{
    int sum = 0;

    switch (hFunction)
    {
    // Misplaced Tiles Heuristic
    case misplacedTiles:
    {
        int numOfMisplacedTiles = 0;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                // Check if the tile is not blank and not in its goal position
                if (board[i][j] != 0 && board[i][j] != goalBoard[i][j])
                {
                    numOfMisplacedTiles++;
                }
            }
        }
        sum = numOfMisplacedTiles;
        break;
    }

    // Manhattan Distance Heuristic
    case manhattanDistance:
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                // Skip the blank tile (0)
                if (board[i][j] != 0)
                {
                    bool found = false;
                    // Search for the current tile's goal position
                    for (int x = 0; x < 3 && !found; x++)
                    {
                        for (int y = 0; y < 3 && !found; y++)
                        {
                            if (goalBoard[x][y] == board[i][j])
                            {
                                // Calculate Manhattan distance: |x1 - x2| + |y1 - y2|
                                sum += abs(i - x) + abs(j - y);
                                found = true; // Stop searching once we've found the goal position
                            }
                        }
                    }
                    // Error checking: ensure every tile has a matching goal position
                    if (!found)
                    {
                        cout << "No match found for tile " << board[i][j] << endl;
                    }
                }
            }
        }
        break;
    }

    default:
        // If an unknown heuristic is passed, throw an exception
        throw std::invalid_argument("Unknown heuristic function");
    }

    // Return the calculated heuristic value
    return sum;
}
// converts board state into its string representation
string Puzzle::toString()
{
    int n;
    string stringPath;

    n = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            stringPath.insert(stringPath.end(), board[i][j] + '0');
            n++;
        }
    }

    //  cout << "toString = " << stringPath << endl;

    return stringPath;
}

bool Puzzle::goalMatch()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] != goalBoard[i][j] && board[i][j] != 0)
            { // Exclude the blank tile (0) from comparison
                return false;
            }
        }
    }
    return true; // If all non-zero tiles match, it's a goal state
}

bool Puzzle::canMoveLeft()
{
    return (x0 > 0);
}

const string Puzzle::getPath()
{
    return path;
}

bool Puzzle::canMoveRight()
{

    return (x0 < 2);
}

bool Puzzle::canMoveUp()
{

    return (y0 > 0);
}

bool Puzzle::canMoveDown()
{

    return (y0 < 2);
}

///////////////////////////////////////////////
// these functions will be useful for Progressive Deepening Search

bool Puzzle::canMoveLeft(int maxDepth)
{

    bool m = false;
    // put your implementations here
    return m;
}
bool Puzzle::canMoveRight(int maxDepth)
{

    bool m = false;
    // put your implementations here
    return m;
}

bool Puzzle::canMoveUp(int maxDepth)
{

    bool m = false;
    // put your implementations here
    return m;
}

bool Puzzle::canMoveDown(int maxDepth)
{

    bool m = false;
    // put your implementations here
    return m;
}

///////////////////////////////////////////////

Puzzle *Puzzle::moveLeft()
{

    Puzzle *p = new Puzzle(*this);

    if (x0 > 0)
    {

        p->board[y0][x0] = p->board[y0][x0 - 1];
        p->board[y0][x0 - 1] = 0;

        p->x0--;

        p->path = path + "L";
        p->pathLength = pathLength + 1;
        p->depth = depth + 1;
    }
    p->strBoard = p->toString();

    return p;
}

Puzzle *Puzzle::moveRight()
{

    Puzzle *p = new Puzzle(*this);

    if (x0 < 2)
    {

        p->board[y0][x0] = p->board[y0][x0 + 1];
        p->board[y0][x0 + 1] = 0;

        p->x0++;

        p->path = path + "R";
        p->pathLength = pathLength + 1;

        p->depth = depth + 1;
    }

    p->strBoard = p->toString();

    return p;
}

Puzzle *Puzzle::moveUp()
{

    Puzzle *p = new Puzzle(*this);

    if (y0 > 0)
    {

        p->board[y0][x0] = p->board[y0 - 1][x0];
        p->board[y0 - 1][x0] = 0;

        p->y0--;

        p->path = path + "U";
        p->pathLength = pathLength + 1;

        p->depth = depth + 1;
    }
    p->strBoard = p->toString();

    return p;
}

Puzzle *Puzzle::moveDown()
{

    Puzzle *p = new Puzzle(*this);

    if (y0 < 2)
    {

        p->board[y0][x0] = p->board[y0 + 1][x0];
        p->board[y0 + 1][x0] = 0;

        p->y0++;

        p->path = path + "D";
        p->pathLength = pathLength + 1;

        p->depth = depth + 1;
    }
    p->strBoard = p->toString();

    return p;
}

/////////////////////////////////////////////////////

void Puzzle::printBoard()
{
    cout << "board: " << endl;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << endl
                 << "board[" << i << "][" << j << "] = " << board[i][j];
        }
    }
    cout << endl;
}

int Puzzle::getPathLength() const
{
    return pathLength;
}
