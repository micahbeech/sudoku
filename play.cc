#include "play.h"

#include <iostream>
#include <fstream>

Play::Play(std::vector<std::string> &boards) {

    if (boards.empty()) {
        std::cerr << "No boards provided. Could not play" << std::endl;
        return;
    }

    int boardIndex = rand() % boards.size();

    std::string filename = boards[boardIndex];
    std::ifstream f{filename};
    if (f.fail()) {
        std::cerr << "Could not open " << filename << std::endl;
        return;
    }

    std::string solutionFile = filename.substr(0, filename.length() - 4);
    solutionFile = solutionFile + "solution.txt";
    std::ifstream sol{solutionFile};
    if (sol.fail()) {
        std::cerr << "Could not open " << solutionFile << std::endl;
        return;
    }

    std::vector<std::vector<char>> table{BOARD_SIZE, std::vector<char>{}};

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

    std::vector<std::vector<char>> table1{BOARD_SIZE, std::vector<char>{}};

    row = 0;
    col = 0;

    while (sol >> c) {
        if (col == BOARD_SIZE) {
            col = 0;
            ++row;
        }
        try {
            table1.at(row).push_back(c);
        } catch (...) {
            std::cerr << "Must provide a 9 x 9 playing board. Could not fill board." << std::endl;
            return;
        }
        ++col;
    }

    try {
        solution = Board{table1};
    } catch (...) {
        std::cerr << "Board was not the right size. Could not fill board." << std::endl;
        return;
    }
}

bool Play::isWon() {
    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            try {
                if (board.getContents().at(row).at(col) != solution.getContents().at(row).at(col)) {
                    return false;
                }
            } catch (...) {
                std::cerr << "Tried to access an invalid board location" << std::endl;
                return false;
            }
        }
    }
    std::cout << "Congratulations, you win!" << std::endl;
    return true;
}

void Play::run() {

    std::string cmd;

    std::cout << board;

    int mistakes = 5;

    while (!isWon()) {

        if (!(std::cin >> cmd)) {
            std::cout << "Invalid command." << std::endl;
            break;
        }

        for (auto &c : cmd) c = ::tolower(c);

        if (cmd == "i" || cmd == "insert") {

            int row;
            int col;
            char c;

            if (!(std::cin >> row && std::cin >> col && std::cin >> c)) {
                std::cout << "Didn't get that. Try again" << std::endl;
                continue;
            }

            try {
                if (solution.getContents().at(row).at(col) == c) {
                    board.insert(row, col, c);
                } else {
                    if (--mistakes > 0) {
                        std::cout << "Not quite! " << mistakes << " mistakes left." << std::endl;
                    } else {
                        std::cout << "No mistakes left! You lose :(" << std::endl;
                        break;
                    }
                }
            } catch (...) {
                std::cout << "Please provide a valid row and column" << std::endl;
                std::cerr << "Tried to access an invalid board location" << std::endl;
            }

        } else if (cmd == "s" || cmd == "solve") {
            board = solution;

        } else if (cmd == "q" || cmd == "quit") {
            std::cout << "Quitting..." << std::endl;
            break;

        } else {
            std::cout << "Command not recognized. Try again." << std::endl;
            
        }

        std::cout << board;

    }

    
}