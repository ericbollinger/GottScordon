#ifndef Piece_H
#define Piece_H
#include "Piece.h"

class Bishop : public Piece {
    
    private:

    public:
        std::vector<int> getMoves();
        char draw();
        Bishop(int x, int y, bool human);
        ~Bishop();
        
};

#endif
