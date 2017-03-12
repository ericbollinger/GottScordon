#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>

#include "Bishop.h"
#include "King.h"
#include "Knight.h"
#include "Pawn.h"
#include "Rook.h"

class Board {

    private:
        std::vector< std::vector<int> > board;
        std::vector<Piece*> pieceList;

    public:
        Board();
        void drawBoard();
        std::vector<int> getAllMoves();
};
