#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <sstream>
#include "Board.h"

class Game {

    private:
        Board board;
        bool didSomeoneWin;

    public:
        Game();
        int colToInt(char c);
        char colToChar(int i);
        int decodeSpace(std::string space);
        std::string encodeSpace(int space);
        void showAllHumanMoves();

};
