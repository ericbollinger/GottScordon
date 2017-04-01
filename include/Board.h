#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include "Move.h"

class Board {

    private:
        std::vector<int> board;

    public:
        Board();
        char drawPiece(int p);
        void drawBoard();
        std::vector<Move> getHumanMoves();
        std::vector<Move> getComputerMoves();
        int getPieceAt(int n);
        void makeMove(Move move);
        void undoMove(Move move);
        int checkBothKings();
};
