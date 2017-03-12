#ifndef Piece_H
#define Piece_H
#include "Piece.h"

class Pawn : public Piece {
    
    private:

    public:
        std::vector<int> getMoves();
        char draw();
        Pawn(int x, int y, bool human);
        ~Pawn();
        
};

#endif
