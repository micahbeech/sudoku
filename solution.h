#ifndef SOLUTION_H
#define SOLUTION_H

class Solution {

  public:
  
    // solves the sudoku puzzle given by board
    void solveSudoku(Board& board);

    // sorts the list of places into ascending order of row
    void sortPlacesRows(std::vector<std::pair<int,int>> &places);

    // sorts the list of places into ascending order of column
    void sortPlacesCols(std::vector<std::pair<int,int>> &places);

    void sortPlacesBoxes(std::vector<std::pair<int,int>> &places);

    // inserts any c at any place in places that can be inserted into board
    bool insert(Board &board, char c);

    // returns a vector of all possible locations on the board that c could go
    std::vector<std::pair<int,int>> placeOptions(Board &board, char c);

    // returns true if c is in row
    bool rowContains(Board &board, int row, char c);

    // returns true if c is in col
    bool colContains(Board &board, int col, char c);

    // returns true if c is in box, where boxes are numbered:
    //      0 | 1 | 2
    //      3 | 4 | 5
    //      6 | 7 | 8
    bool boxContains(Board &board, int row, int col, char c);

};

#endif
