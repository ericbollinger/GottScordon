#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>

class Board {

    private:
        std::vector<int> board;

    public:
        Board();
        char drawPiece(int p);
        void drawBoard();
        std::vector<int> getHumanMoves();
        std::vector<int> getComputerMoves();
        void makeMove(int from, int to);
};
