#include "board.h"
#include "solution.h"
#include "solutionTest.h"
#include "play.h"

#include <string>
#include <iostream>

int main() {

    std::string version;
    std::cin >> version;

    for (auto &c : version) c = ::tolower(c);



    if (version == "play") {
        std::vector<std::string> boards{"boards/board2.txt"};
        Play play{boards};
        play.run();

    } else if (version == "solutiontest") {
        Solution sol{};
        Board board{};
        SolutionTest solTest{board, sol};
        solTest.run();

    } else {
        std::cout << "Didn't get that." << std::endl;

    }

}
