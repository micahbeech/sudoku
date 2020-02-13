#include "board.h"
#include "solution.h"
#include "solutionTest.h"

int main() {

    Solution sol{};
    Board board{};

    SolutionTest solTest{board, sol};
    solTest.run();

}