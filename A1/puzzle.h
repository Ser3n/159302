#include <string>
#include <iostream>

using namespace std;

enum heuristicFunction
{
    misplacedTiles,
    manhattanDistance
};

class Puzzle
{

private:
    string path;
    int pathLength;
    int hCost;
    int fCost;
    int depth;

    int goalBoard[3][3];

    int x0, y0; // coordinates of the blank or 0-tile

    int board[3][3];

public:
    string strBoard;

    Puzzle(const Puzzle &p); // Constructor
    Puzzle(string const elements, string const goal);

    string getGoalState() const;

    void printBoard();

    int h(heuristicFunction hFunction) const;
    void updateFCost();
    void updateHCost(heuristicFunction hFunction);
    void updateDepth()
    {
        depth++;
    }

    bool goalMatch();
    string toString();

    string getString()
    {
        return strBoard;
    }

    bool canMoveLeft();
    bool canMoveRight();
    bool canMoveUp();
    bool canMoveDown();

    //----------------------------------------
    // these functions will be useful for Progressive Deepening Search
    bool canMoveLeft(int maxDepth);
    bool canMoveDown(int maxDepth);
    bool canMoveRight(int maxDepth);
    bool canMoveUp(int maxDepth);
    //----------------------------------------

    Puzzle *moveUp();
    Puzzle *moveRight();
    Puzzle *moveDown();
    Puzzle *moveLeft();

    const string getPath();

    void setDepth(int d);
    int getDepth();

    int getPathLength() const;
    int getFCost() const;
    int getHCost() const;
    int getGCost() const;
};
