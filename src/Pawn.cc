#include "Pawn.h"

Pawn::Pawn(int x, int y, bool human) : Piece::Piece(x, y, human, 99) {
    std::cout << "x: " << x << ", y: " << y << "\n";
}

Pawn::~Pawn(void) {}

std::vector<int> Pawn::getMoves() {
    std::vector<int> foo(1,1);
    return foo;
}

char Pawn::draw() {
    if (this->getHuman()) {
        return 'p';
    } else {
        return 'P';
    }
}
