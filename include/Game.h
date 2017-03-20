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

    public:
        Game();
        int colToInt(char c);
        char colToChar(int i);
        int decodeSpace(std::string space);
        std::string encodeSpace(int space);
        void inputMove();
        void makeComputerMove();
        int min(int depth, int alpha);
        int max(int depth, int beta);
        void checkForGameEnd();
        void gameEnd(bool humanWins);
        int evaluate();

};
