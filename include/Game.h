#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <sstream>
#include "Board.h"

class Game {

    private:
        Board board;
        int maxDepth;
        time_t turnEnd;

    public:
        Game();
        int colToInt(char c);
        char colToChar(int i);
        int decodeSpace(std::string space);
        std::string encodeSpace(int space);
        std::string reverseMove(Move move);
        void inputMove();
        void resetMaxDepth();
        bool endTurnNow();
        void increaseMaxDepth();
        void makeComputerMove();
        int min(int depth, int alpha);
        int max(int depth, int beta);
        void checkForGameEnd();
        void gameEnd(int endStatus);
        int evaluate();

};
