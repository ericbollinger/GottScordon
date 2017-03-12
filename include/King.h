#ifndef Piece_H
#define Piece_H
#include "Piece.h"

class King : public Piece {
    
    private:

    public:
        std::vector<int> getMoves();
        char draw();
        King(int x, int y, bool human);
        ~King();
        
};

#endif
