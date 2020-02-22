#include <iostream>
#include <vector>

#include "solutionTest.h"
#include "play.h"

int main() {

    std::string version;
    std::cin >> version;

    for (auto &c : version) c = ::tolower(c);

    if (version == "play") {
        const int board_start = 2;
        const int board_end = 4;

        std::vector<std::string> boards;
        for (int i = board_start; i <= board_end; ++i) {
            boards.push_back("boards/board" + std::to_string(i) + ".txt");
        }

        Play play{boards};
        play.run();

    } else if (version == "solutiontest") {
        SolutionTest solTest{};
        solTest.run();

    } else {
        std::cout << "Didn't get that." << std::endl;

    }

}
