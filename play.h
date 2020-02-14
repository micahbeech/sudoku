#ifndef PLAY_H
#define PLAY_H

#include "board.h"

class Play {
    
    Board board;
    Board solution;

    bool isWon();

  public:
    
    Play(std::vector<std::string> &boards);

    void run();

};

#endif
