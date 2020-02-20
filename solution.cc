#include <vector>
#include <iostream>
#include <utility>

#include "board.h"
#include "solution.h"

// solves the sudoku puzzle given by board
void Solution::solveSudoku(Board& board) {
    std::vector<char> characters{'1','2','3','4','5','6','7','8','9'};
    bool didInsert = true;
    while (didInsert) {
        didInsert = false;
        for (auto c : characters) {
            if (insert(board, c)) didInsert = true;
        }
    }
}

// sorts the list of places into ascending order of row
void Solution::sortPlacesRows(std::vector<std::pair<int,int>> &places) {
    for (auto i = places.begin(); i != places.end(); ++i) {
        auto smallest = i;
        for (auto j = i + 1; j != places.end(); ++j) {
            if (j->first < smallest->first) smallest = j;
        }
        if (i != smallest) std::swap(*i, *smallest);
    }
}

// sorts the list of places into ascending order of column
void Solution::sortPlacesCols(std::vector<std::pair<int,int>> &places) {
    for (auto i = places.begin(); i != places.end(); ++i) {
        auto smallest = i;
        for (auto j = i + 1; j != places.end(); ++j) {
            if (j->second < smallest->second) smallest = j;
        }
        if (i != smallest) std::swap(*i, *smallest);
    }
}

// sorts the list into the boxes they are in
void Solution::sortPlacesBoxes(std::vector<std::pair<int,int>> &places) {
    for (auto i = places.begin(); i != places.end(); ++i) {
        auto smallest = i;
        for (auto j = i + 1; j != places.end(); ++j) {
            int box1 = (j->first / BOX_WIDTH) * BOX_WIDTH + j->second / BOX_WIDTH;
            int box2 = (smallest->first / BOX_WIDTH) * BOX_WIDTH + smallest->second / BOX_WIDTH;
            if (box1 < box2) smallest = j;
        }
        if (i != smallest) std::swap(*i, *smallest);
    }
}

// inserts any c at any place in places that can be inserted into board
bool Solution::insert(Board &board, char c) {

    // get all places that c could go on the board
    std::vector<std::pair<int,int>> places = placeOptions(board, c);

    int i = 0;
	sortPlacesRows(places);

    while (i < places.size()) {

        // if places[i] is the only option in its row, insert it
        if (i == places.size() - 1 || places[i].first != places[i+1].first) {
            board.insert(places[i].first, places[i].second, c);
	        return true;
        }

        // skip to the next row
        int row = places[i].first;
        do { ++i; } while (i < places.size() && places[i].first == row);

    }

    i = 0;
    sortPlacesCols(places);

    while (i < places.size()) {

        // if places[i] is the only option in its column, insert it
        if (i == places.size() - 1 || places[i].second != places[i+1].second) {
            board.insert(places[i].first, places[i].second, c);
	        return true;
        }

        // skip to the next column
        int col = places[i].second;
        do { ++i; } while (i < places.size() && places[i].second == col);

    }

    i = 0;
    sortPlacesBoxes(places);

    while (i < places.size()) {

        // if places[i] is the only option in its box, insert it
        if (i == places.size() - 1) {
            board.insert(places[i].first, places[i].second, c);
	        return true;
        } 
        int box1 = (places[i].first / BOX_WIDTH) * BOX_WIDTH + places[i].second / BOX_WIDTH;
        int box2 = (places[i+1].first / BOX_WIDTH) * BOX_WIDTH + places[i+1].second / BOX_WIDTH;
        if (box1 != box2) {
            board.insert(places[i].first, places[i].second, c);
	        return true;
        }

        // skip to next box
	    int box = (places[i].first / BOX_WIDTH) * BOX_WIDTH + places[i].second / BOX_WIDTH;
        do { ++i; } while (i < places.size() && box == (places[i].first / BOX_WIDTH) * BOX_WIDTH + places[i].second / BOX_WIDTH);

    }

    // did not insert c anywhere in the board
    return false;
}

// returns a vector of all possible locations on the board that c could go
std::vector<std::pair<int,int>> Solution::placeOptions(Board &board, char c) {

    std::vector<std::pair<int,int>> places;

    for (int n = 0; n < BOARD_SIZE; ++n) {

        for (int m = 0; m < BOARD_SIZE; ++m) {

            try {
                // it is an option if it isn't in this box, row, column and there isn't already a number here
                if (board.getContents().at(n).at(m) == '.' && !boxContains(board, n, m, c) && !rowContains(board, n, c) && !colContains(board, m, c)) {
                    places.push_back(std::make_pair(n, m));
                }

            } catch (...) {
                std::cerr << "Board is invalid size." << std::endl;
                return std::vector<std::pair<int,int>>{};

            }

        }
    }

    return places;
}

// returns true if c is in row
bool Solution::rowContains(Board &board, int row, char c) {
    try {
        for (auto place : board.getContents().at(row)) {
            if (place == c) return true;
        }
    } catch (...) {
        std::cerr << "Error: Failed to access row contents for row " << row << std::endl;
        return false;
    }
    return false;
}

// returns true if c is in col
bool Solution::colContains(Board &board, int col, char c) {
    for (auto row : board.getContents()) {
        try {
            if (row.at(col) == c) return true;
        } catch (...) {
            std::cerr << "Error: Failed to access column contents for column " << col << std::endl;
            return false;
        }
    }
    return false;
}

// returns true if c is in box, where boxes are numbered:
//      0 | 1 | 2
//      3 | 4 | 5
//      6 | 7 | 8
bool Solution::boxContains(Board &board, int row, int col, char c) {
    if (row < 0 || row >= BOARD_SIZE) return false;
    if (col < 0 || col >= BOARD_SIZE) return false;
    
    row = (row / BOX_WIDTH) * BOX_WIDTH;
    col = (col / BOX_WIDTH) * BOX_WIDTH;
    for (int i = row; i < row + BOX_WIDTH; ++i) {
        for (int j = col; j < col + BOX_WIDTH; ++j) {
            try {
                if (board.getContents().at(i).at(j) == c) return true;
            } catch (...) {
                std::cerr << "Error: Failed to access box contents for box " << (row / BOX_WIDTH) * BOX_WIDTH + col % BOX_WIDTH << std::endl;
                return false;
            }
        }
    }
    
    return false;
}
