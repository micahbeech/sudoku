#ifndef BOARD_H
#define BOARD_H

#include <vector>

class Board {

    std::vector<std::vector<char>> board;

  public:

    Board();

    Board(const std::vector<std::vector<char>> &board);

    Board(std::initializer_list<char> init);

    std::vector<std::vector<char>> &getContents();

    void insert(int row, int col, char c);

};

std::ostream& operator<< (std::ostream &os, Board &board);

#endif