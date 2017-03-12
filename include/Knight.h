#ifndef Piece_H
#define Piece_H
#include "Piece.h"

class Knight : public Piece {
    
    private:

    public:
        std::vector<int> getMoves();
        char draw();
        Knight(int x, int y, bool human);
        ~Knight();
        
};

#endif
