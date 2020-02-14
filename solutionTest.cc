
#include "board.h"
#include "solution.h"
#include "solutionTest.h"

#include <string>
#include <iostream>
#include <vector>
#include <utility>
#include <fstream>

SolutionTest::SolutionTest(Board &board, Solution &sol) : board{board}, sol{sol} {}

void SolutionTest::empty() {
    board = Board{};
}

void SolutionTest::fill() {

    std::vector<std::vector<char>> table{BOARD_SIZE, std::vector<char>{}};

    std::string filename;
    std::cin >> filename;
    std::ifstream f{filename};
    if (f.fail()) {
        std::cerr << "Could not open " << filename << std::endl;
        return;
    }

    char c;
    int row = 0;
    int col = 0;

    while (f >> c) {
        if (col == BOARD_SIZE) {
            col = 0;
            ++row;
        }
        try {
            table.at(row).push_back(c);
        } catch (...) {
            std::cerr << "Must provide a 9 x 9 playing board. Could not fill board." << std::endl;
            return;
        }
        ++col;
    }

    try {
        board = Board{table};
    } catch (...) {
        std::cerr << "Board was not the right size. Could not fill board." << std::endl;
        return;
    }
}

void SolutionTest::solve() {
    sol.solveSudoku(board);
}

void SolutionTest::sortRows() {
    std::vector<std::pair<int,int>> pairs;

    int i,j;
    while (std::cin >> i && i >= 0 && std::cin >> j) {
        std::pair<int,int> pair = std::make_pair(i, j);
        pairs.push_back(pair);
    }
    
    std::cout << "Pairs before sort:" << std::endl;
    for (auto pair : pairs) {
        std::cout << "(" << pair.first << "," << pair.second << ") ";
    }
    std::cout << std::endl;

    sol.sortPlacesRows(pairs);

    std::cout << "Pairs after sort:" << std::endl;
    for (auto pair : pairs) {
        std::cout << "(" << pair.first << "," << pair.second << ") ";
    }
    std::cout << std::endl;
}

void SolutionTest::sortCols() {
    std::vector<std::pair<int,int>> pairs;

    int i,j;
    while (std::cin >> i && i >= 0 && std::cin >> j) {
        std::pair<int,int> pair = std::make_pair(i, j);
        pairs.push_back(pair);
    }
    
    std::cout << "Pairs before sort:" << std::endl;
    for (auto pair : pairs) {
        std::cout << "(" << pair.first << "," << pair.second << ") ";
    }
    std::cout << std::endl;

    sol.sortPlacesCols(pairs);

    std::cout << "Pairs after sort:" << std::endl;
    for (auto pair : pairs) {
        std::cout << "(" << pair.first << "," << pair.second << ") ";
    }
    std::cout << std::endl;
}

void SolutionTest::sortBoxes() {
    std::vector<std::pair<int,int>> pairs;

    int i,j;
    while (std::cin >> i && i >= 0 && std::cin >> j) {
        std::pair<int,int> pair = std::make_pair(i, j);
        pairs.push_back(pair);
    }
    
    std::cout << "Pairs before sort:" << std::endl;
    for (auto pair : pairs) {
        std::cout << "(" << pair.first << "," << pair.second << ") ";
    }
    std::cout << std::endl;

    sol.sortPlacesBoxes(pairs);

    std::cout << "Pairs after sort:" << std::endl;
    for (auto pair : pairs) {
        std::cout << "(" << pair.first << "," << pair.second << ") ";
    }
    std::cout << std::endl;
}

void SolutionTest::rowContains() {
    int row;
    char c;

    std::cin >> row;
    std::cin >> c;
    bool result = sol.rowContains(board, row, c);

    std::cout << c << " is in row " << row << ": ";
    std::cout << std::boolalpha << result << std::endl;
}

void SolutionTest::colContains() {
    int col;
    char c;

    std::cin >> col;
    std::cin >> c;
    bool result = sol.colContains(board, col, c);

    std::cout << c << " is in column " << col << ": ";
    std::cout << std::boolalpha << result << std::endl;
}

void SolutionTest::boxContains() {
    int box;
    char c;

    std::cin >> box;
    std::cin >> c;

    int row = box;
    int col = (box % 3) * 3;
    bool result = sol.boxContains(board, row, col, c);

    std::cout << c << " is in box " << box << ": ";
    std::cout << std::boolalpha << result << std::endl;
}

void SolutionTest::rowOptions() {
    char c;
    std::cin >> c;

    std::vector<int> rows = sol.rowOptions(board, c);

    std::cout << c << " can go in row(s): ";
    for (auto row : rows) {
        std::cout << row << " ";
    }
    std::cout << std::endl;
}

void SolutionTest::colOptions() {
    char c;
    std::cin >> c;

    std::vector<int> cols = sol.colOptions(board, c);

    std::cout << c << " can go in column(s): ";
    for (auto col : cols) {
        std::cout << col << " ";
    }
    std::cout << std::endl;
}

void SolutionTest::placeOptions() {
    char c;
    std::cin >> c;

    std::vector<int> rows = sol.rowOptions(board, c);
    std::vector<int> cols = sol.colOptions(board, c);

    std::vector<std::pair<int,int>> places = sol.placeOptions(board, rows, cols, c);

    std::cout << c << " can go in these places: ";
    for (auto pair : places) {
        std::cout << "(" << pair.first << "," << pair.second << ") ";
    }
    std::cout << std::endl;
}

void SolutionTest::lower(std::string &s) {
    for (auto &c : s) c = ::tolower(c);
}

void SolutionTest::run() {

    std::string cmd;

    while (std::cin >> cmd) {

        lower(cmd);

        if (cmd == "empty") {
            empty();

        } else if (cmd == "fill") {
            fill();

        } else if (cmd == "solve") {
            solve();

        } else if (cmd == "sortrows") {
            sortRows();

        } else if (cmd == "sortcols") {
            sortCols();

        } else if (cmd == "sortboxes") {
            sortBoxes();

        } else if (cmd == "rowcontains") {
            rowContains();

        } else if (cmd == "colcontains") {
            colContains();

        } else if (cmd == "boxcontains") {
            boxContains();

        } else if (cmd == "rowoptions") {
            rowOptions();

        } else if (cmd == "coloptions") {
            colOptions();

        } else if (cmd == "placeoptions") {
            placeOptions();

        } else if (cmd == "print" || cmd == "p") {
            std::cout << board;

        } else if (cmd == "quit" || cmd == "q") {
            std::cout << "Quitting..." << std::endl;
            break;

        } else {
            std::cout << "Command not recognized. Please try again." << std::endl;

        }

    }
}
