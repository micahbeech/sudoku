#include <vector>
#include <cassert>
#include <iostream>

#include "board.h"

Board::Board() {
    size_t boardSize = 9;
    std::vector<char> col{'.','.','.','.','.','.','.','.','.'};
    std::vector<std::vector<char>> board{boardSize, col};
    this->board = board;
}

Board::Board(const std::vector<std::vector<char>> &board) : board(board) {

    // board must be 9 x 9
    if (board.size() != 9) throw;
    for (auto col : board) {
        if (col.size() != 9) throw;
    }

}

Board::Board(std::initializer_list<char> init) {

    assert(init.size() == 81);

    board.reserve(9);

    int i = 0;
    int j = 0;

    std::vector<char> col;
    col.reserve(9);
    board.push_back(col);

    for (auto c : init) {
        if (j < 9) {
            ++j;
        } else {
            j = 1;
            ++i;
            std::vector<char> col;
            col.reserve(9);
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
    assert(row < 9);
    assert(col < 9);
    assert(row >= 0);
    assert(col >= 0);
    try{
        // if (board.at(row).at(col) != '.') {
        //     std::cout << "Replacing existing value in board." << std::endl;
        // }
        board.at(row).at(col) = c;
    } catch (...) {
        std::cerr << "Tried to insert a character at an invalid board location" << std::endl;
        std::abort();
    }
    
}

std::ostream& operator<< (std::ostream &os, Board &board) {
    int j = 0;
    for (auto row : board.getContents()) {
        if (j == 0 || j == 3 || j == 6) {
            os << "-------------------------" << std::endl;
        }
        ++j;
        int i = 0;
        for (auto c : row) {
            if (i == 0 || i == 3 || i == 6) {
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
