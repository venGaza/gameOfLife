// This is a simulation for Conway's Game of Life! It has four rules:
// -If a cell has 0 or 1 neighbors, it dies.
// -If a cell has 2 neighbors, it remains stable.
// -If a cell has 3 neighbors, it creates life.
// -If a cell has 4 or more neighbors, it dies.

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "console.h"
#include "filelib.h"
#include "grid.h"
#include "gwindow.h"
#include "simpio.h"
#include "strlib.h"
#include "lifegui.h"
using namespace std;

/*Function prototypes*/
void welcomeMessage();
void gridInput(Grid<bool> &currentGrid);
void worldType(bool &wrap);
void printWorld(const Grid<bool> &currentWorld);
char animationType();
void animateWorld(Grid<bool> &currentWorld, const bool wrap, char &choice);
void tickNoWrap(Grid<bool> &currentWorld);
void tickWrap(Grid<bool> &currentWorld);
void deadOrAlive(Grid<bool> &currentWorld, int &neighborCount, const int row, const int col);

/*Constants*/
const char ALIVE = 'X';
const char DEAD = '-';

/*Main Function*/
int main() {
    Grid<bool> currentWorld;
    bool wrap;
    char choice;

    welcomeMessage();
    gridInput(currentWorld);
    worldType(wrap);
    printWorld(currentWorld);
    choice = animationType();
    while (choice != 'q'){
        animateWorld(currentWorld, wrap, choice);
    }

    cout << "Have a nice Life!" << endl;
    return 0;
}

/*
 * Function: welcomeMessage
 * Usage: welcomeMessage()
 * -------------------------
 * Prints a welcome message to the screen and explains
 * what the program does.
*/
void welcomeMessage() {
    cout << "Welcome to the CS 106B Game of Life, \n"
         << "a simulation of the lifecycle of a bacteria colony. \n"
         << "Cells (X) live and die by the following rules: \n"
         << "- A cell with 1 or fewer neighbors dies. \n"
         << "- Locations with 2 neighbors remain stable.\n"
         << "- Locations with 3 neighbors will create life. \n"
         << "- A cell with 4 more neighbors dies. \n " << endl;
}

/*
 * Function gridInput(Grid<bool> &currentWorld)
 * Usage: gridInput(currentWorld)
 * -------------------------------------------
 * This function reads in a user file to create
 * a boolean grid.
*/
void gridInput(Grid<bool> &currentWorld) {
    string row;
    string column;
    string line;

    ifstream stream;
    string fileName = promptUserForFile(stream, "Grid input file name?");

    getline(stream, row);
    int gridRows = stringToInteger(row);

    getline(stream, column);
    int gridColumns = stringToInteger(column);

    currentWorld.resize(gridRows, gridColumns);

    for(int i = 0; i < gridRows; i++){
        getline(stream, line);
        for(int j = 0; j < gridColumns; j++){
            if (line[j] == ALIVE){
                currentWorld[i][j] = true;
            }else{
                currentWorld[i][j] = false;
            }
        }
    }

    stream.close();
}

/*
 * Function worldType(bool &wrap)
 * Usage: worldType(wrap)
 * ------------------------------
 * The user decides if the world will wrap around
 * or not.
*/
void worldType(bool &wrap){
    wrap = getYesOrNo("Should the simulation wrap around the grid?");
}

/*
 * Function printWorld(const Grid<bool> &currentWorld)
 * Usage: printWorld(currentWorld)
 * ---------------------------------------------------
 * Prints the current world to the console.
*/
void printWorld(const Grid<bool> &currentWorld){
    for(int i = 0; i < currentWorld.numRows(); i++){
        for(int j = 0; j < currentWorld.numCols(); j++){
            if (currentWorld[i][j]){
                cout << ALIVE;
            }else{
                cout << DEAD;
            }
        }
        cout << endl;
    }
}

/*
 * Function animationType
 * Usage: choice = animationType()
 * ---------------------------------------------------
 * Allows the user to select the way the world will
 * proceed forward and returns the selection.
*/
char animationType(){
    string choice = getLine("a)nimate, t)ick, q)uit?");
    choice = toLowerCase(choice);

    while (true){
        if (choice.length() > 1){
            cout << "Please select a valid choice" << endl;
            choice = getLine("a)nimate, t)ick, q)uit?");
            choice = toLowerCase(choice);
        }else if (choice[0] == 'a'){
            break;
        }else if (choice[0] == 't'){
            break;
        }else if (choice[0] == 'q'){
            break;
        }else{
            cout << "Please select a valid choice" << endl;
            choice = getLine("a)nimate, t)ick, q)uit?");
            choice = toLowerCase(choice);
        }
    }
    return choice[0];
}

/*
 * Function animateWorld
 * Usage: animateWorld(Grid<bool> &currentWorld, const bool wrap, char &choice)
 * ---------------------------------------------------------------------------
 * Based on user input, the world will proceed forward to demonstrate
 * Conway's Life algorithm.
*/
void animateWorld(Grid<bool> &currentWorld, const bool wrap, char &choice){
    if(wrap && choice == 'a'){
        int numFrames = getInteger("How many frames?");
        cout << "(" << numFrames << " new generations are shown, with screen clear and " <<
                "50 ms pause before each)"<< endl;

        pause(3000); //3 second pause for user to read output

        for (int i = 0; i < numFrames; i++){
            clearConsole();
            tickWrap(currentWorld);
            pause(50);
        }
    }else if(wrap && choice == 't'){
        tickWrap(currentWorld);
    }else if(!wrap && choice == 'a'){
        int numFrames = getInteger("How many frames?");
        cout << "(" << numFrames << " new generations are shown, with screen clear and " <<
                "50 ms pause before each)"<< endl;

        pause(3000); //3 second pause for user to read output

        for (int i = 0; i < numFrames; i++){
            clearConsole();
            tickNoWrap(currentWorld);
            pause(50);
        }
    }else{
        tickNoWrap(currentWorld);
    }

    choice = animationType();
}

/*
 * Function tickNoWrap
 * Usage: tickNoWrap(currentWorld)
 * ---------------------------------------------------------------------------
 * Moves the world forward by one generation and does not wrap around the edges.
*/
void tickNoWrap(Grid<bool> &currentWorld){
    Grid<bool> tempWorld = currentWorld;
    int neighborCount = 0;

    for(int i = 0; i < currentWorld.nRows; i++){
        for(int j = 0; j < currentWorld.nCols; j++){
            if(tempWorld.inBounds(i - 1, j - 1)){       //Top-Left-Diagonal
                if(tempWorld[i - 1][j - 1]){
                    neighborCount++;
                }
            }

            if(tempWorld.inBounds(i - 1, j)){           //Top-Center
                if(tempWorld[i - 1][j]){
                    neighborCount++;
                }
            }

            if(tempWorld.inBounds(i - 1, j + 1)){       //Top-Right-Diagonal
                if(tempWorld[i - 1][j + 1]){
                    neighborCount++;
                }
            }

            if(tempWorld.inBounds(i, j - 1)){           //Middle-Left
                if(tempWorld[i][j - 1]){
                    neighborCount++;
                }
            }

            if(tempWorld.inBounds(i - 1, j + 1)){       //Middle-Right
                if(tempWorld[i][j + 1]){
                    neighborCount++;
                }
            }

            if(tempWorld.inBounds(i + 1, j - 1)){       //Bottom-Left-Diagonal
                if(tempWorld[i + 1][j - 1]){
                    neighborCount++;
                }
            }

            if(tempWorld.inBounds(i + 1, j)){           //Bottom-Center
                if(tempWorld[i + 1][j]){
                    neighborCount++;
                }
            }

            if(tempWorld.inBounds(i + 1, j + 1)){       //Bottom-Right-Diagonal
                if(tempWorld[i + 1][j + 1]){
                    neighborCount++;
                }
            }

            deadOrAlive(currentWorld, neighborCount, i, j);
        }
    }
    printWorld(currentWorld);
}

/*
 * Function tickWrap
 * Usage: tickWrap(currentWorld)
 * ---------------------------------------------------------------------------
 * Moves the world forward by one generation and wraps around edges.
*/
void tickWrap(Grid<bool> &currentWorld){
    Grid<bool> tempWorld = currentWorld;
    int neighborCount = 0;
    int numRows = currentWorld.numRows();
    int numCols = currentWorld.numCols();

    for(int i = 0; i < numRows; i++){
        for(int j = 0; j < numCols; j++){
            if(tempWorld.inBounds(i - 1, j - 1)){       //Top-Left-Diagonal
                if(tempWorld[i - 1][j - 1]){
                    neighborCount++;
                }
            }else{
                if(tempWorld[(i - 1 + numRows) % numRows][(j - 1 + numCols) % numCols]){
                    neighborCount++;
                }
            }

            if(tempWorld.inBounds(i - 1, j)){           //Top-Center
                if(tempWorld[i - 1][j]){
                    neighborCount++;
                }
            }else{
                if(tempWorld[(i - 1 + numRows) % numRows][j]){
                    neighborCount++;
                }
            }

            if(tempWorld.inBounds(i - 1, j + 1)){       //Top-Right-Diagonal
                if(tempWorld[i - 1][j + 1]){
                    neighborCount++;
                }
            }else{
                if(tempWorld[(i - 1 + numRows) % numRows][(j + 1 + numCols) % numCols]){
                    neighborCount++;
                }
            }

            if(tempWorld.inBounds(i, j - 1)){           //Middle-Left
                if(tempWorld[i][j - 1]){
                    neighborCount++;
                }
            }else{
                if(tempWorld[i][(j - 1 + numCols) % numCols]){
                    neighborCount++;
                }
            }

            if(tempWorld.inBounds(i - 1, j + 1)){       //Middle-Right
                if(tempWorld[i][j + 1]){
                    neighborCount++;
                }
            }else{
                if(tempWorld[i][(j + 1 + numCols) % numCols]){
                    neighborCount++;
                }
            }

            if(tempWorld.inBounds(i + 1, j - 1)){       //Bottom-Left-Diagonal
                if(tempWorld[i + 1][j - 1]){
                    neighborCount++;
                }
            }else{
                if(tempWorld[(i + 1 + numRows) % numRows][(j - 1 + numCols) % numCols]){
                    neighborCount++;
                }
            }

            if(tempWorld.inBounds(i + 1, j)){           //Bottom-Center
                if(tempWorld[i + 1][j]){
                    neighborCount++;
                }
            }else{
                if(tempWorld[(i + 1 + numRows) % numRows][j]){
                    neighborCount++;
                }
            }

            if(tempWorld.inBounds(i + 1, j + 1)){       //Bottom-Right-Diagonal
                if(tempWorld[i + 1][j + 1]){
                    neighborCount++;
                }
            }else{
                if(tempWorld[(i + 1 + numRows) % numRows][(j + 1 + numCols) % numCols]){
                    neighborCount++;
                }
            }

            deadOrAlive(currentWorld, neighborCount, i, j);
        }
    }
    printWorld(currentWorld);
}

/*
 * Function deadOrAlive
 * Usage: deadOrAlive(currentWorld, 5, 9, 9)
 * ---------------------------------------------------------------------------
 * Determines if the grid cell lives or dies.
*/
void deadOrAlive (Grid<bool> &currentWorld, int &neighborCount, const int row, const int col){
    if (neighborCount <= 1 || neighborCount >= 4){
        currentWorld[row][col] = false;
    }else if(neighborCount == 2){
        currentWorld[row][col] = currentWorld[row][col];
    }else if(neighborCount == 3){
        currentWorld[row][col] = true;
    }

    neighborCount = 0; //resets neighborCounter for next iteration
}
