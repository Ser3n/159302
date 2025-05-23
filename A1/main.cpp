//////////////////////////////////////////////////////////////////////////
//  8-PUZZLE PROBLEM
//  
//  Start-up codes by n.h.reyes@massey.ac.nz
//
//  Name(s):
//  Date:
//
//////////////////////////////////////////////////////////////////////////
/*
 * Flicker-free implementation of the 8-puzzle board game using the BGI
 * graphics library for Windows.
 */


#if defined __unix__ || defined __APPLE__
    #include <stdio.h>
    #include <stdlib.h>
    #include <sstream>
    #include <iostream>
    #include <iomanip>
    #include <algorithm> //used by transform - to lower case
    #include <exception>
    #include <chrono>
    #include <graphics.h>

    #include "algorithm.h"

#elif defined __WIN32__

    #include <windows.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <sstream>
    #include <iostream>
    #include <iomanip>
    #include <algorithm> //used by transform - to lower case
    #include <exception>
    #include <chrono>

    #include "graphics.h"
    #include "algorithm.h"

#endif

using namespace std;

//////////////////////////////////////////////////////////////////////////////////////////////////////
string list_of_initialStates[5] = { "120483765","208135467","704851632","536407182","638541720" };
string goalState = string("123456780");
//////////////////////////////////////////////////////////////////////////////////////////////////////

int g_local_loops_avoided;

#define OUTPUT_LENGTH 2 /* Length of output string. */

const int HEIGHT = 400; /**< Height of board for rendering in pixels. */
const int WIDTH  = 400; /**< Width of board for rendering in pixels. */

/**
 * Update the board and draw it to the screen. This function displays the
 * board updates in a flicker-free way.
 *
 * @param board 3 x 3 array containing the current board state,
 *              0 indicates an empty space.
 */


//////////////////////////////////////////////////////
// Function prototypes
void displayBoard(string const elements); 
void AnimateSolution(string const initialState, string const goalState, string path);

////////////////////////////////////////////////////// 
 

void update(int **board) {
    /* Setting up the graphics. */
    static bool setup = false;

    if(!setup) {
        //int graphDriver = 0;
        //int graphMode = 0;
        //initgraph(&graphDriver, &graphMode, "", WIDTH, HEIGHT);
        // int GraphDriver=DETECT,GraphMode;
        // initgraph( &GraphDriver, &GraphMode, "" ); // Start Window
        setup = true;
    }

    /* Variables for the function. */
    int xIncrement = (WIDTH - 40) / 3;        /* Grid's raster width. */
    int yIncrement = ((HEIGHT - 6) - 40) / 3; /* Grid's raster height. */
    int x = 0;            /* Temporary x positions. */
    int y = 0;            /* Temporary y positions. */
    char outputString[OUTPUT_LENGTH]; /* Holder for output strings in the GUI. */
    static bool visual;   /* Indicator which visual page to draw to
                           * to prevent flickers. */

    /* Initalising the variables. */
    strncpy(outputString, "", OUTPUT_LENGTH);
    /* Even though this is not necessary here the protected version of "strcpy"
       is used in this case. It should ALWAYS be used to prevent boundary
       overwrites! */

    /* Initialising the GUI. */
    setactivepage(visual);
    setbkcolor(BLACK);
    cleardevice();
    setfillstyle(SOLID_FILL, WHITE);
    settextstyle(GOTHIC_FONT, HORIZ_DIR, 6);
    settextjustify(CENTER_TEXT, CENTER_TEXT);

    /* Display different coloured squares for different numbers. */
    y = 10;
    for(int i = 0; i < 3; i++) {
        x = 10;
        for(int j = 0; j < 3; j++) {
            if(board[i][j] != 0) {
                setcolor(board[i][j]);
                bar(x, y, x + xIncrement, y + yIncrement);
            }
            x += 10;
            x += xIncrement;
        }
        y += 10;
        y += yIncrement;
    }

    /* Display the actual numbers. */
    y = 8 * HEIGHT / 40;
    for(int i = 0; i < 3; i++) {
        x = WIDTH / 6;
        for(int j = 0; j < 3; j++) {
            setcolor(WHITE);
            setbkcolor(board[i][j]);
            if(board[i][j] != 0) {
                snprintf(outputString, OUTPUT_LENGTH, "%d", board[i][j]);
                /* Even though this is also not necessary here the protected
                   version of "sprintf" is used in this case. It should ALWAYS
                   be used to prevent boundary overwrites! */
                outtextxy(x, y, outputString);
                moveto(0, 0);
            }
            x += 2 * (WIDTH / 6);
        }
        y += 13 * HEIGHT / 40;
    }

    /* Set the page to display. */
    setvisualpage(visual);
    visual = !visual;

    delay(100);
}


void displayBoard(string const elements) {
    /* Setting up the graphics. */
    
    int board[3][3];
        
    int n=0;
    
    for(int i=0; i < 3;i++){
        for(int j=0; j < 3;j++){
            
            board[i][j] = elements.at(n) - '0';     
            n++;            
         }   
     }
    
    


    /* Variables for the function. */
    int xIncrement = (WIDTH - 40) / 3;        /* Grid's raster width. */
    int yIncrement = ((HEIGHT - 6) - 40) / 3; /* Grid's raster height. */
    int x = 0;            /* Temporary x positions. */
    int y = 0;            /* Temporary y positions. */
    char outputString[OUTPUT_LENGTH]; /* Holder for output strings in the GUI. */
    static bool visual;   /* Indicator which visual page to draw to
                           * to prevent flickers. */

    /* Initalising the variables. */
    strncpy(outputString, "", OUTPUT_LENGTH);
    /* Even though this is not necessary here the protected version of "strcpy"
       is used in this case. It should ALWAYS be used to prevent boundary
       overwrites! */

    /* Initialising the GUI. */
    setactivepage(visual);
    
    cleardevice();
    setfillstyle(SOLID_FILL, WHITE);
    settextstyle(GOTHIC_FONT, HORIZ_DIR, 6);
    settextjustify(CENTER_TEXT, CENTER_TEXT);

    /* Display different coloured squares for different numbers. */
    y = 10;
    for(int i = 0; i < 3; i++) {
        x = 10;
        for(int j = 0; j < 3; j++) {
            if(board[i][j] != 0) {
                // setcolor(board[i][j]);
                setfillstyle(SOLID_FILL, board[i][j] % MAXCOLORS);
                bar(x, y, x + xIncrement, y + yIncrement);
            }
            x += 10;
            x += xIncrement;
        }
        y += 10;
        y += yIncrement;
    }

    /* Display the actual numbers. */
    y = 8 * HEIGHT / 40;
    for(int i = 0; i < 3; i++) {
        x = WIDTH / 6;
        for(int j = 0; j < 3; j++) {
            // setcolor(WHITE);
            // setbkcolor(board[i][j]);
            if(board[i][j] != 0) {
                snprintf(outputString, OUTPUT_LENGTH, "%d", board[i][j]);
                /* Even though this is also not necessary here the protected
                   version of "sprintf" is used in this case. It should ALWAYS
                   be used to prevent boundary overwrites! */
//                outtextxy(x, y, (char *)elements[i+j*3]);   
                settextjustify(CENTER_TEXT, CENTER_TEXT);
                outtextxy(x, y, outputString);
                moveto(0, 0);
            }
            x += 2 * (WIDTH / 6);
        }
        y += 13 * HEIGHT / 40;
    }

    /* Set the page to display. */
    setvisualpage(visual);
    visual = !visual;

    delay(100);
}



void AnimateSolution(string const initialState, string const goalState, string path){

    int step=1;
   
    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 3);
    settextjustify(CENTER_TEXT, CENTER_TEXT);
    outtextxy(getmaxx()/2,getmaxy()/2,const_cast<char*>("press any key to start."));
    cout << endl << endl << "press any key to start." << endl << endl;
    getch();
    
    cout << endl << "--------------------------------------------------------------------" << endl;
    if (path==""){
         cout << endl << "Nothing to animate." << endl;
    } else {
        cout << endl << "Animating solution..." << endl;
        cout << "Plan of action = " << path << endl;
    }
    
    Puzzle *p = new Puzzle(initialState, goalState);
    Puzzle *nextState=NULL;
    
    string strState;
        
    strState = p->toString();
    displayBoard(strState);
    
    cout << "--------------------------------------------------------------------" << endl;
          
    for(long long unsigned int i=0; i < path.length(); i++){
        
       cout << endl << "Step #" << step << ")  ";
       switch(path[i]){
            
            case 'U': nextState = p->moveUp(); cout << "[UP]" << endl;
                      break;
            case 'D': nextState = p->moveDown(); cout << "[DOWN]" << endl;
                      break;
            case 'L': nextState = p->moveLeft(); cout << "[LEFT]" << endl;
                      break;
            case 'R': nextState = p->moveRight(); cout << "[RIGHT]" << endl;
                      break;
      }
      strState = nextState->toString();
        
      delete p;
      p = nextState;
        
      displayBoard(strState);
      
      step++;
    }
    
    delete p; //clear memory    
    cout << endl << "Animation done." << endl;
    cout << "--------------------------------------------------------------------" << endl;
    

}


///////////////////////////////////////////////////////////////////////////////////////////////
void run_all_experiments() {

    int num_of_init_states = sizeof(list_of_initialStates) / sizeof(list_of_initialStates[0]);

    int pathLength = 0;
    // int depth = 0;
    int numOfStateExpansions = 0;
    int maxQLength = 0;
    int numOfDeletionsFromMiddleOfHeap = 0;
    int numOfLocalLoopsAvoided = 0;
    int numOfAttemptedNodeReExpansions = 0;
    float actualRunningTime = 0.0;

    string initialState;

    std::cout << "ALGORITHM,               INIT_STATE,            GOAL_STATE,       PATH_LENGTH,     STATE_EXPANSIONS,  MAX_QLENGTH,  RUNNING_TIME,  DELETIONS_MIDDLE_HEAP, LOCAL_LOOPS_AVOIDED, ATTEMPTED_REEXPANSIONS,   PATH" << endl;

    //---
    for (int j = 0; j < num_of_init_states; j++) {

        initialState = list_of_initialStates[j];

        string path;
        path.clear();
        pathLength = 0;
        // depth = 0;
        numOfStateExpansions = 0;
        maxQLength = 0;
        numOfDeletionsFromMiddleOfHeap = 0;
        numOfLocalLoopsAvoided = 0;
        numOfAttemptedNodeReExpansions = 0;
        actualRunningTime = 0.0;
        path = uc_explist(initialState, goalState, pathLength, numOfStateExpansions, maxQLength, actualRunningTime, numOfDeletionsFromMiddleOfHeap, numOfLocalLoopsAvoided, numOfAttemptedNodeReExpansions);


        std::cout << setw(21) << "uniform_cost_search";
        std::cout << setprecision(6) << std::setfill(' ') << std::fixed << std::right << ' ' << setw(10) << "," << initialState;
        std::cout << setprecision(6) << std::setfill(' ') << std::fixed << std::right << ' ' << setw(10) << "," << goalState;
        std::cout << setprecision(6) << std::setfill(' ') << std::fixed << std::right << ' ' << setw(10) << "," << pathLength;
        std::cout << setprecision(6) << std::setfill(' ') << std::fixed << std::right << ' ' << setw(10) << "," << numOfStateExpansions;
        std::cout << setprecision(6) << std::setfill(' ') << std::fixed << std::right << ' ' << setw(10) << "," << maxQLength;
        std::cout << setprecision(6) << std::setfill(' ') << std::fixed << std::right << ' ' << setw(10) << "," << actualRunningTime;
        std::cout << setprecision(6) << std::setfill(' ') << std::fixed << std::right << ' ' << setw(10) << "," << numOfDeletionsFromMiddleOfHeap;
        std::cout << setprecision(6) << std::setfill(' ') << std::fixed << std::right << ' ' << setw(10) << "," << numOfLocalLoopsAvoided;
        std::cout << setprecision(6) << std::setfill(' ') << std::fixed << std::right << ' ' << setw(10) << "," << numOfAttemptedNodeReExpansions;
        std::cout << setprecision(6) << std::setfill(' ') << std::fixed << std::right << ' ' << setw(10) << "," << path << endl;


    } //End - For loop
    //---
    for (int j = 0; j < num_of_init_states; j++) {

        initialState = list_of_initialStates[j];

        string path;
        path.clear();
        pathLength = 0;
        // depth = 0;
        numOfStateExpansions = 0;
        maxQLength = 0;
        numOfDeletionsFromMiddleOfHeap = 0;
        numOfLocalLoopsAvoided = 0;
        numOfAttemptedNodeReExpansions = 0;
        actualRunningTime = 0.0;
        path = aStar_ExpandedList(initialState, goalState, pathLength, numOfStateExpansions, maxQLength, actualRunningTime, numOfDeletionsFromMiddleOfHeap, numOfLocalLoopsAvoided, numOfAttemptedNodeReExpansions, misplacedTiles);

                                  
        std::cout << setw(21) << "astar_misplacedtiles";
        std::cout << setprecision(6) << std::setfill(' ') << std::fixed << std::right << ' ' << setw(10) << "," << initialState;
        std::cout << setprecision(6) << std::setfill(' ') << std::fixed << std::right << ' ' << setw(10) << "," << goalState;
        std::cout << setprecision(6) << std::setfill(' ') << std::fixed << std::right << ' ' << setw(10) << "," << pathLength;
        std::cout << setprecision(6) << std::setfill(' ') << std::fixed << std::right << ' ' << setw(10) << "," << numOfStateExpansions;
        std::cout << setprecision(6) << std::setfill(' ') << std::fixed << std::right << ' ' << setw(10) << "," << maxQLength;
        std::cout << setprecision(6) << std::setfill(' ') << std::fixed << std::right << ' ' << setw(10) << "," << actualRunningTime;
        std::cout << setprecision(6) << std::setfill(' ') << std::fixed << std::right << ' ' << setw(10) << "," << numOfDeletionsFromMiddleOfHeap;
        std::cout << setprecision(6) << std::setfill(' ') << std::fixed << std::right << ' ' << setw(10) << "," << numOfLocalLoopsAvoided;
        std::cout << setprecision(6) << std::setfill(' ') << std::fixed << std::right << ' ' << setw(10) << "," << numOfAttemptedNodeReExpansions;
        std::cout << setprecision(6) << std::setfill(' ') << std::fixed << std::right << ' ' << setw(10) << "," << path << endl;


     } //End - For loop
    //---
    for (int j = 0; j < num_of_init_states; j++) {

        initialState = list_of_initialStates[j];

        string path;
        path.clear();
        pathLength = 0;
        // depth = 0;
        numOfStateExpansions = 0;
        maxQLength = 0;
        numOfDeletionsFromMiddleOfHeap = 0;
        numOfLocalLoopsAvoided = 0;
        numOfAttemptedNodeReExpansions = 0;
        actualRunningTime = 0.0;
        path = aStar_ExpandedList(initialState, goalState, pathLength, numOfStateExpansions, maxQLength, actualRunningTime, numOfDeletionsFromMiddleOfHeap, numOfLocalLoopsAvoided, numOfAttemptedNodeReExpansions, manhattanDistance);

                                  
        std::cout << setw(21) << "astar_manhattan";
        std::cout << setprecision(6) << std::setfill(' ') << std::fixed << std::right << ' ' << setw(10) << "," << initialState;
        std::cout << setprecision(6) << std::setfill(' ') << std::fixed << std::right << ' ' << setw(10) << "," << goalState;
        std::cout << setprecision(6) << std::setfill(' ') << std::fixed << std::right << ' ' << setw(10) << "," << pathLength;
        std::cout << setprecision(6) << std::setfill(' ') << std::fixed << std::right << ' ' << setw(10) << "," << numOfStateExpansions;
        std::cout << setprecision(6) << std::setfill(' ') << std::fixed << std::right << ' ' << setw(10) << "," << maxQLength;
        std::cout << setprecision(6) << std::setfill(' ') << std::fixed << std::right << ' ' << setw(10) << "," << actualRunningTime;
        std::cout << setprecision(6) << std::setfill(' ') << std::fixed << std::right << ' ' << setw(10) << "," << numOfDeletionsFromMiddleOfHeap;
        std::cout << setprecision(6) << std::setfill(' ') << std::fixed << std::right << ' ' << setw(10) << "," << numOfLocalLoopsAvoided;
        std::cout << setprecision(6) << std::setfill(' ') << std::fixed << std::right << ' ' << setw(10) << "," << numOfAttemptedNodeReExpansions;
        std::cout << setprecision(6) << std::setfill(' ') << std::fixed << std::right << ' ' << setw(10) << "," << path << endl;


    } //End - For loop

}


///////////////////////////////////////////////////////////////////////////////////////////////
void run_uc_experiments() {

    int num_of_init_states = sizeof(list_of_initialStates) / sizeof(list_of_initialStates[0]);

    int pathLength = 0;
    // int depth = 0;
    int numOfStateExpansions = 0;
    int maxQLength = 0;
    int numOfDeletionsFromMiddleOfHeap = 0;
    int numOfLocalLoopsAvoided = 0;
    int numOfAttemptedNodeReExpansions = 0;
    float actualRunningTime = 0.0;

    string initialState;

    std::cout << "ALGORITHM,               INIT_STATE,            GOAL_STATE,       PATH_LENGTH,     STATE_EXPANSIONS,  MAX_QLENGTH,  RUNNING_TIME,  DELETIONS_MIDDLE_HEAP, LOCAL_LOOPS_AVOIDED, ATTEMPTED_REEXPANSIONS,   PATH" << endl;

    for (int j = 0; j < num_of_init_states; j++) {

        initialState = list_of_initialStates[j];

        string path;
        path.clear();
        pathLength = 0;
        // depth = 0;
        numOfStateExpansions = 0;
        maxQLength = 0;
        numOfDeletionsFromMiddleOfHeap = 0;
        numOfLocalLoopsAvoided = 0;
        numOfAttemptedNodeReExpansions = 0;
        actualRunningTime = 0.0;
        path = uc_explist(initialState, goalState, pathLength, numOfStateExpansions, maxQLength, actualRunningTime, numOfDeletionsFromMiddleOfHeap, numOfLocalLoopsAvoided, numOfAttemptedNodeReExpansions);


        std::cout << setw(16) << "uniform_cost_search";
        std::cout << setprecision(6) << std::setfill(' ') << std::fixed << std::right << ' ' << setw(10) << "," << initialState;
        std::cout << setprecision(6) << std::setfill(' ') << std::fixed << std::right << ' ' << setw(10) << "," << goalState;
        std::cout << setprecision(6) << std::setfill(' ') << std::fixed << std::right << ' ' << setw(10) << "," << pathLength;
        std::cout << setprecision(6) << std::setfill(' ') << std::fixed << std::right << ' ' << setw(13) << "," << numOfStateExpansions;
        std::cout << setprecision(6) << std::setfill(' ') << std::fixed << std::right << ' ' << setw(15) << "," << maxQLength;
        std::cout << setprecision(6) << std::setfill(' ') << std::fixed << std::right << ' ' << setw(15) << "," << actualRunningTime;
        std::cout << setprecision(6) << std::setfill(' ') << std::fixed << std::right << ' ' << setw(15) << "," << numOfDeletionsFromMiddleOfHeap;
        std::cout << setprecision(6) << std::setfill(' ') << std::fixed << std::right << ' ' << setw(20) << "," << numOfLocalLoopsAvoided;
        std::cout << setprecision(6) << std::setfill(' ') << std::fixed << std::right << ' ' << setw(15) << "," << numOfAttemptedNodeReExpansions;
        std::cout << setprecision(6) << std::setfill(' ') << std::fixed << std::right << ' ' << setw(15) << "," << path << endl;


    } //End - For loop

}

///////////////////////////////////////////////////////////////////////////////////////////////
void run_astar_manhattan_experiments() {

    int num_of_init_states = sizeof(list_of_initialStates) / sizeof(list_of_initialStates[0]);

    int pathLength = 0;
    // int depth = 0;
    int numOfStateExpansions = 0;
    int maxQLength = 0;
    int numOfDeletionsFromMiddleOfHeap = 0;
    int numOfLocalLoopsAvoided = 0;
    int numOfAttemptedNodeReExpansions = 0;
    float actualRunningTime = 0.0;

    string initialState; 

    std::cout << "ALGORITHM,               INIT_STATE,            GOAL_STATE,       PATH_LENGTH,     STATE_EXPANSIONS,  MAX_QLENGTH,  RUNNING_TIME,  DELETIONS_MIDDLE_HEAP, LOCAL_LOOPS_AVOIDED, ATTEMPTED_REEXPANSIONS,   PATH" << endl;

    for (int j = 0; j < num_of_init_states; j++) {

            initialState = list_of_initialStates[j];

            string path;
            path.clear();
            pathLength = 0;
            // depth = 0;
            numOfStateExpansions = 0;
            maxQLength = 0;
            numOfDeletionsFromMiddleOfHeap = 0;
            numOfLocalLoopsAvoided = 0;
            numOfAttemptedNodeReExpansions = 0;
            actualRunningTime = 0.0;
            path = aStar_ExpandedList(initialState, goalState, pathLength, numOfStateExpansions, maxQLength, actualRunningTime, numOfDeletionsFromMiddleOfHeap, numOfLocalLoopsAvoided, numOfAttemptedNodeReExpansions, manhattanDistance);

            
            std::cout << setw(16) << "astar_manhattan";
            std::cout << setprecision(6) << std::setfill(' ') << std::fixed << std::right << ' ' << setw(10) << "," << initialState;
            std::cout << setprecision(6) << std::setfill(' ') << std::fixed << std::right << ' ' << setw(10) << "," << goalState;
            std::cout << setprecision(6) << std::setfill(' ') << std::fixed << std::right << ' ' << setw(10) << "," << pathLength;
            std::cout << setprecision(6) << std::setfill(' ') << std::fixed << std::right << ' ' << setw(13) << "," << numOfStateExpansions;
            std::cout << setprecision(6) << std::setfill(' ') << std::fixed << std::right << ' ' << setw(15) << "," << maxQLength;
            std::cout << setprecision(6) << std::setfill(' ') << std::fixed << std::right << ' ' << setw(15) << "," << actualRunningTime;
            std::cout << setprecision(6) << std::setfill(' ') << std::fixed << std::right << ' ' << setw(15) << "," << numOfDeletionsFromMiddleOfHeap;
            std::cout << setprecision(6) << std::setfill(' ') << std::fixed << std::right << ' ' << setw(20) << "," << numOfLocalLoopsAvoided;
            std::cout << setprecision(6) << std::setfill(' ') << std::fixed << std::right << ' ' << setw(15) << "," << numOfAttemptedNodeReExpansions;
            std::cout << setprecision(6) << std::setfill(' ') << std::fixed << std::right << ' ' << setw(15) << "," << path << endl;
            

    } //End - For loop

}

///////////////////////////////////////////////////////////////////////////////////////////////
void run_astar_misplaced_tiles_experiments() {

    int num_of_init_states = sizeof(list_of_initialStates) / sizeof(list_of_initialStates[0]);

    int pathLength = 0;
    // int depth = 0;
    int numOfStateExpansions = 0;
    int maxQLength = 0;
    int numOfDeletionsFromMiddleOfHeap = 0;
    int numOfLocalLoopsAvoided = 0;
    int numOfAttemptedNodeReExpansions = 0;
    float actualRunningTime = 0.0;

    string initialState;

    std::cout << "ALGORITHM,               INIT_STATE,            GOAL_STATE,       PATH_LENGTH,     STATE_EXPANSIONS,  MAX_QLENGTH,  RUNNING_TIME,  DELETIONS_MIDDLE_HEAP, LOCAL_LOOPS_AVOIDED, ATTEMPTED_REEXPANSIONS,   PATH" << endl;

    for (int j = 0; j < num_of_init_states; j++) {

        initialState = list_of_initialStates[j];

        string path;
        path.clear();
        pathLength = 0;
        // depth = 0;
        numOfStateExpansions = 0;
        maxQLength = 0;
        numOfDeletionsFromMiddleOfHeap = 0;
        numOfLocalLoopsAvoided = 0;
        numOfAttemptedNodeReExpansions = 0;
        actualRunningTime = 0.0;
        path = aStar_ExpandedList(initialState, goalState, pathLength, numOfStateExpansions, maxQLength, actualRunningTime, numOfDeletionsFromMiddleOfHeap, numOfLocalLoopsAvoided, numOfAttemptedNodeReExpansions, misplacedTiles);


        std::cout << setw(16) << "astar_misplacedtiles";
        std::cout << setprecision(6) << std::setfill(' ') << std::fixed << std::right << ' ' << setw(10) << "," << initialState;
        std::cout << setprecision(6) << std::setfill(' ') << std::fixed << std::right << ' ' << setw(10) << "," << goalState;
        std::cout << setprecision(6) << std::setfill(' ') << std::fixed << std::right << ' ' << setw(10) << "," << pathLength;
        std::cout << setprecision(6) << std::setfill(' ') << std::fixed << std::right << ' ' << setw(13) << "," << numOfStateExpansions;
        std::cout << setprecision(6) << std::setfill(' ') << std::fixed << std::right << ' ' << setw(15) << "," << maxQLength;
        std::cout << setprecision(6) << std::setfill(' ') << std::fixed << std::right << ' ' << setw(15) << "," << actualRunningTime;
        std::cout << setprecision(6) << std::setfill(' ') << std::fixed << std::right << ' ' << setw(15) << "," << numOfDeletionsFromMiddleOfHeap;
        std::cout << setprecision(6) << std::setfill(' ') << std::fixed << std::right << ' ' << setw(20) << "," << numOfLocalLoopsAvoided;
        std::cout << setprecision(6) << std::setfill(' ') << std::fixed << std::right << ' ' << setw(15) << "," << numOfAttemptedNodeReExpansions;
        std::cout << setprecision(6) << std::setfill(' ') << std::fixed << std::right << ' ' << setw(15) << "," << path << endl;


    } //End - For loop

}
///////////////////////////////////////////////////////////////////////////////////////////////



/**
 * Main function to kick off the game.
 */



int main( int argc, char* argv[] ){
   
   string path;
   cout << "Debug: Entering main function" << endl;
  

	if(argc < 3){
        cout << "<< SEARCH ALGORITHMS >>" << endl;
		cout << "please include missing parameters." << endl;
        cout << "SYNTAX #1: search.exe <TYPE_OF_RUN = \"batch_run\" or \"single_run\" or \"animate_run\"> ALGORITHM_NAME \"INITIAL STATE\" \"GOAL STATE\" " << endl;
        cout << "SYNTAX #2: search.exe <TYPE_OF_RUN = \"batch_run\"> ALGORITHM_NAME" << endl;
		exit(0);
	}
    
	
	string typeOfRun(argv[1]);
	string algorithmSelected(argv[2]);

    string initialState;
    string goalState;

    if (argc > 3) {
        initialState = string(argv[3]);
        goalState = string(argv[4]);

    }
	
    std::transform(typeOfRun.begin(), typeOfRun.end(), typeOfRun.begin(), ::tolower);
    std::transform(algorithmSelected.begin(), algorithmSelected.end(), algorithmSelected.begin(), ::tolower);
    

	int pathLength=0;
	// int depth=0;
    int numOfStateExpansions=0;	
	int maxQLength=0;
    int numOfDeletionsFromMiddleOfHeap=0;
    int numOfLocalLoopsAvoided=0;
    int numOfAttemptedNodeReExpansions=0;

	float actualRunningTime=0.0;	
	
#if defined __unix__ || defined __APPLE__
    // init graphics
    int GraphDriver=DETECT,GraphMode;
    initgraph( &GraphDriver, &GraphMode, const_cast<char*>("") ); // Start Window

#elif defined __WIN32__    
    // init graphics
    int graphDriver = 0;
    int graphMode = 0;
    initgraph(&graphDriver, &graphMode, "", WIDTH, HEIGHT);   
#endif

	
try{
    if( (typeOfRun == "single_run") || (typeOfRun == "animate_run") ){
        if (argc < 5) {
            cout << "<< SEARCH ALGORITHMS >>" << endl;
            cout << "please include missing parameters." << endl;
            cout << "SYNTAX #1: search.exe <TYPE_OF_RUN = \"batch_run\" or \"single_run\" or \"animate_run\"> ALGORITHM_NAME \"INITIAL STATE\" \"GOAL STATE\" " << endl;
            cout << "SYNTAX #2: search.exe <TYPE_OF_RUN = \"batch_run\"> ALGORITHM_NAME" << endl;
            exit(0);
        }
        //---
        cout << endl << "============================================<< EXPERIMENT RESULTS >>============================================" << endl;

        if (algorithmSelected == "uc_explist") {
            cout << "Debug: About to call uc_explist" << endl;
            cout << setw(31) << std::left << "1) uc_explist";


        }
        else if (algorithmSelected == "astar_explist_misplacedtiles") {
            cout << setw(31) << std::left << "2) astar_explist_misplacedtiles";

        }
        else if (algorithmSelected == "astar_explist_manhattan") {
            cout << setw(31) << std::left << "3) astar_explist_manhattan";
        }
        //---

        if (algorithmSelected == "uc_explist") {
            cout << "Debug: About to call uc_explist" << endl;

            path = uc_explist(initialState, goalState, pathLength, numOfStateExpansions, maxQLength, actualRunningTime, numOfDeletionsFromMiddleOfHeap, numOfLocalLoopsAvoided, numOfAttemptedNodeReExpansions);

        }
       
        else if (algorithmSelected == "astar_explist_misplacedtiles") {

            path = aStar_ExpandedList(initialState, goalState, pathLength, numOfStateExpansions, maxQLength, actualRunningTime, numOfDeletionsFromMiddleOfHeap, numOfLocalLoopsAvoided, numOfAttemptedNodeReExpansions, misplacedTiles);

        }
        else if (algorithmSelected == "astar_explist_manhattan") {

            
            path = aStar_ExpandedList(initialState, goalState, pathLength, numOfStateExpansions, maxQLength, actualRunningTime, numOfDeletionsFromMiddleOfHeap,numOfLocalLoopsAvoided ,numOfAttemptedNodeReExpansions, manhattanDistance);

        }

    } else if(typeOfRun == "batch_run") {

        if (algorithmSelected == "uc_explist") {

            run_uc_experiments();

        }else if (algorithmSelected == "astar_explist_misplacedtiles") {

            run_astar_misplaced_tiles_experiments();

        }else if (algorithmSelected == "astar_explist_manhattan") {

            run_astar_manhattan_experiments();

        }else if (algorithmSelected == "all") {
            using std::chrono::system_clock;
            system_clock::time_point start;             
            start = std::chrono::system_clock::now();

            run_all_experiments();

            auto end = std::chrono::system_clock::now();
            std::chrono::duration<double> elapsed_seconds = end-start;
            string timeStr = to_string(elapsed_seconds.count()); 
            timeStr = timeStr + " sec.";
            cout << "\nTotal time = " << timeStr << endl;

        }

    }
   

}

catch(exception &e){
    cout << "Standard exception: " << e.what() << endl;
}
     

	if(typeOfRun == "batch_run"){	
	  //nothing to do

    }
    else if ((typeOfRun == "single_run") || (typeOfRun == "animate_run") ){
        if (pathLength == 0) cout << "\n\n*---- NO SOLUTION found. (Q is empty!) ----*" << endl;

        cout << setprecision(6) << setw(25) << std::setfill(' ') << std::right << endl << endl << "Initial State:" << std::fixed << ' ' << setw(12) << initialState << endl;
        cout << setprecision(6) << setw(25) << std::setfill(' ') << std::right << "Goal State:" << std::fixed << ' ' << setw(12) << goalState << endl;
        cout << setprecision(6) << setw(25) << std::setfill(' ') << std::right << endl << "Path Length:" << std::fixed << ' ' << setw(12) << pathLength << endl;
        cout << setprecision(6) << setw(25) << std::setfill(' ') << std::right << "Num Of State Expansions:" << std::fixed << ' ' << setw(12) << numOfStateExpansions << endl;
        cout << setprecision(6) << setw(25) << std::setfill(' ') << std::right << "Max Q Length:" << std::fixed << ' ' << setw(12) << maxQLength << endl;
        cout << setprecision(6) << setw(25) << std::setfill(' ') << std::right << "Actual Running Time:" << std::fixed << ' ' << setprecision(6) << setw(12) << actualRunningTime << endl;

        cout << setprecision(6) << setw(25) << std::setfill(' ') << std::right << "Num of Deletions from MiddleOfHeap:" << std::fixed << ' ' << setprecision(6) << setw(12) << numOfDeletionsFromMiddleOfHeap << endl;
        cout << setprecision(6) << setw(25) << std::setfill(' ') << std::right << "Num of Attempted Node ReExpansions:" << std::fixed << ' ' << setprecision(6) << setw(12) << numOfAttemptedNodeReExpansions << endl;


        cout << "================================================================================================================" << endl << endl;

    }  
    
    if(typeOfRun == "animate_run"){
        if (pathLength == 0) cout << "\n\n*---- NO SOLUTION found. (Q is empty!) ----*" << endl;

        if (path != "") {            
            AnimateSolution(initialState, goalState, path);            
        }
	}
    
    closegraph();
    
    // Show that we have exited without an error. 
    return 0;
}


