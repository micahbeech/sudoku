#include <vector>
#include <cassert>
#include <iostream>

#include "board.h"

class BAD_BOARD_SIZE{};

Board::Board() {
    std::vector<char> col{'.','.','.','.','.','.','.','.','.'};
    std::vector<std::vector<char>> board{BOARD_SIZE, col};
    this->board = board;
}

Board::Board(const std::vector<std::vector<char>> &board) : board(board) {

    // board must be 9 x 9
    if (board.size() != BOARD_SIZE) throw BAD_BOARD_SIZE{};
    for (auto col : board) {
        if (col.size() != BOARD_SIZE) throw BAD_BOARD_SIZE{};
    }

}

Board::Board(std::initializer_list<char> init) {

    assert(init.size() == BOARD_SIZE * BOARD_SIZE);

    board.reserve(BOARD_SIZE);

    int i = 0;
    int j = 0;

    std::vector<char> col;
    col.reserve(BOARD_SIZE);
    board.push_back(col);

    for (auto c : init) {
        if (j < BOARD_SIZE) {
            ++j;
        } else {
            j = 1;
            ++i;
            std::vector<char> col;
            col.reserve(BOARD_SIZE);
            board.push_back(col);
        }
        try {  
            board.at(i).push_back(c);
        } catch (...) {
            std::cerr << "Tried to add a character to a non-existent row" << std::endl;
            std::abort();
        }
    }

}

std::vector<std::vector<char>> &Board::getContents() { return board; }

void Board::insert(int row, int col, char c) {
    if (!(row < BOARD_SIZE &&
        col < BOARD_SIZE &&
        row >= 0 &&
        col >= 0)) {
            throw BAD_BOARD_SIZE{};
    }
    try{
        board.at(row).at(col) = c;
    } catch (...) {
        std::cerr << "Tried to insert a character at an invalid board location" << std::endl;
        std::abort();
    }
    
}

std::ostream& operator<< (std::ostream &os, Board &board) {
    int j = 0;
    for (auto row : board.getContents()) {
        if (j == 0 || j == BOX_WIDTH || j == BOX_WIDTH * 2) {
            os << "-------------------------" << std::endl;
        }
        ++j;
        int i = 0;
        for (auto c : row) {
            if (i == 0 || i == BOX_WIDTH || i == BOX_WIDTH * 2) {
                os << "| ";
            }
            ++i;
            if (c == '.') {
                os << "  ";
            } else {
                os << c << " ";
            }
        }
        os << "|" << std::endl;
    }
    os << "-------------------------" << std::endl;
    
    return os;
}
