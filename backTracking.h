#ifndef BACKTRACKING_H
#define BACKTRACKING_H

#include <vector>

#include "board.h"

class BackTracking {

  public:

    // solves the sudoku puzzle given by board
    void solveSudoku(Board& board);

    void insert(Board& board);

};

#endif
