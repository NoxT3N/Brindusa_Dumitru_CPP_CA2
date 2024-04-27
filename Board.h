//
// Created by brind on 15/04/2024.
//

#ifndef BRINDUSA_DUMITRU_CA2_BOARD_H
#define BRINDUSA_DUMITRU_CA2_BOARD_H

#include "Bug.h"
#include <vector>

struct Cell {
    Bug* bug;
};

class Board {
private:
    std::vector<std::vector<Cell>> cells;
    std::vector<Bug*> bug_vector;

public:
    Board(vector<Bug*>&);
    ~Board();

    void initializeBoard(const string&);
    void displayBugs();
    void findBug();
};


#endif //BRINDUSA_DUMITRU_CA2_BOARD_H
