#ifndef Piece_H
#define Piece_H
#include "Piece.h"

class Rook : public Piece {
    
    private:

    public:
        std::vector<int> getMoves();
        char draw();
        Rook(int x, int y, bool human);
        ~Rook();
        
};

#endif
