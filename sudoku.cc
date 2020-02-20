#include <iostream>
#include <vector>

#include "solutionTest.h"
#include "play.h"

int main() {

    std::string version;
    std::cin >> version;

    for (auto &c : version) c = ::tolower(c);

    if (version == "play") {
        std::vector<std::string> boards{"boards/board2.txt"};
        Play play{boards};
        play.run();

    } else if (version == "solutiontest") {
        SolutionTest solTest{};
        solTest.run();

    } else {
        std::cout << "Didn't get that." << std::endl;

    }

}
