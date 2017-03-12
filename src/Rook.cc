#include "Rook.h"

Rook::Rook(int x, int y, bool human) : Piece::Piece(x, y, human, 99) {
    std::cout << "x: " << x << ", y: " << y << "\n";
}

Rook::~Rook(void) {}

std::vector<int> Rook::getMoves() {
    std::vector<int> foo(1,1);
    return foo;
}

char Rook::draw() {
    if (this->getHuman()) {
        return 'k';
    } else {
        return 'K';
    }
}
