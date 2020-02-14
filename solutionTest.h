#ifndef RUNTESTS_H
#define RUNTESTS_H

class Board;
class Solution;

class SolutionTest {

    Board board;
    Solution sol;

  public:

    SolutionTest(Board &board, Solution &sol);

    // Runs the tests
    // When prompted, enter the method name you want to run that method
    void run();

  private:

    // Each method refers to a method within solution

    // Fill the board with all '.'
    void empty();

    // Read in characters and fill the board with them
    void fill();

    // Solve the board
    void solve();

    // Read in pairs of integers and sort them by row (first entry)
    void sortRows();

    // Read in pairs of integers and sort them by column (second entry)
    void sortCols();

    // Read in pairs of integers and sort them by box ([row / 3] * 3 + col % 3)
    void sortBoxes();

    // Read in a row and a character, show which columns the character is in
    void rowContains();

    // Read in a column and a character, show which rows the character is in
    void colContains();

    // Read in a box and a character, show which boxes the character is in
    // Boxes are numbered as:
    //      0 | 1 | 2
    //      3 | 4 | 5
    //      6 | 7 | 8
    void boxContains();

    // Read in a character and show which rows it can go in
    void rowOptions();

    // Read in a character and show which columns it can go in
    void colOptions();

    // Read in a character and show which places it can go in on the board
    void placeOptions();

    // Makes all characters in s lowercase
    void lower(std::string &s);

};

#endif
