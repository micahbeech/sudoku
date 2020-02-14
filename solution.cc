#include <vector>
#include <cassert>
#include <iostream>
#include <utility>

#include "board.h"
#include "solution.h"

void Solution::solveSudoku(Board& board) {
    std::vector<char> characters{'1','2','3','4','5','6','7','8','9'};
    bool didInsert = true;
    while (didInsert) {
        didInsert = false;
        for (auto c = characters.begin(); c != characters.end(); ++c) {
            std::vector<std::pair<int,int>> places = placeOptions(board, *c);
            if (insert(board, places, *c)) didInsert = true;
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
            int box1 = (j->first / 3) * 3 + j->second / 3;
            int box2 = (smallest->first / 3) * 3 + smallest->second / 3;
            if (box1 < box2) smallest = j;
        }
        if (i != smallest) std::swap(*i, *smallest);
    }
}

// inserts any c at any place in places that can be inserted into board
bool Solution::insert(Board &board, std::vector<std::pair<int,int>> places, char c) {
    bool inserted = false;
    sortPlacesRows(places);
    int i = 0;
    while (i < places.size()) {
        if (i == places.size() - 1 || places[i].first != places[i+1].first) {
            board.insert(places[i].first, places[i].second, c);
            places = placeOptions(board, c);
            inserted = true;
        } else {
            int row = places[i].first;
            do { ++i; } while (i < places.size() && places[i].first == row);
        }
    }
    sortPlacesCols(places);
    i = 0;
    while (i < places.size()) {
        if (i == places.size() - 1 || places[i].second != places[i+1].second) {
            board.insert(places[i].first, places[i].second, c);
            places = placeOptions(board, c);
            inserted = true;
        } else {
            int col = places[i].second;
            do { ++i; } while (i < places.size() && places[i].second == col);
        }
    }
    sortPlacesBoxes(places);
    i = 0;
    while (i < places.size()) {
        if (i == places.size() - 1) {
            board.insert(places[i].first, places[i].second, c);
            places = placeOptions(board, c);
            inserted = true;
            continue;
        } 
        int box1 = (places[i].first / 3) * 3 + places[i].second / 3;
        int box2 = (places[i+1].first / 3) * 3 + places[i+1].second / 3;
        if (box1 != box2) {
            board.insert(places[i].first, places[i].second, c);
            places = placeOptions(board, c);
            inserted = true;
        } else {
            do { 
                box1 = (places[i].first / 3) * 3 + places[i].second / 3;
                box2 = (places[i+1].first / 3) * 3 + places[i+1].second / 3;
                ++i; 
            } while (i < places.size() && box1 == box2);
        }
    }
    return inserted;
}

std::vector<std::pair<int,int>> Solution::placeOptions(Board &board, char c) {
    std::vector<std::pair<int,int>> places;
    for (int n = 0; n < BOARD_SIZE; ++n) {
        for (int m = 0; m < BOARD_SIZE; ++m) {
            try {
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
    if (row < 0 || row > 8) return false;
    if (col < 0 || col > 8) return false;
    
    row = (row / 3) * 3;
    col = (col / 3) * 3;
    for (int i = row; i < row + 3; ++i) {
        for (int j = col; j < col + 3; ++j) {
            try {
                if (board.getContents().at(i).at(j) == c) return true;
            } catch (...) {
                std::cerr << "Error: Failed to access box contents for box " << (row / 3) * 3 + col % 3 << std::endl;
                return false;
            }
        }
    }
    return false;
}
