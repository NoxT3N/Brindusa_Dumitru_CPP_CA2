//
// Created by brind on 15/04/2024.
//

#ifndef BRINDUSA_DUMITRU_CA2_BOARD_H
#define BRINDUSA_DUMITRU_CA2_BOARD_H

#include "Bug.h"
#include <vector>

struct Cell {
    vector<Bug*> bugs;
    bool isEmpty;

    Cell() : isEmpty(true){}
};

class Board {
private:
    vector<Bug*> bug_vector;
    Cell grid[10][10];
    Bug* winner;
    bool gameOver;

public:
    explicit Board(vector<Bug*>&);
    ~Board();

    void initializeBoard(const string&);
    void displayAllBugs();
    void findBug();
    void tapBoard();
    void runSimulation();
    void displayHistory();
    void displayCells();
    void drawBoard();
    void exit();

    string getBugType(Bug *&);
};


#endif //BRINDUSA_DUMITRU_CA2_BOARD_H
