#include "backTracking.h"
#include "solution.h"

void BackTracking::solveSudoku(Board& board) {

    insert(board);

}

void BackTracking::insert(Board& board) {

    // recursively insert characters into board
    // if a character won't go, try to insert a different one
    // if none can go, pop back to the last viable solution
    // retry

}

// add function that checks if a char can go in a spot
