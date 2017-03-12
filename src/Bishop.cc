#include "Bishop.h"

Bishop::Bishop(int x, int y, bool human) : Piece::Piece(x, y, human, 99) {
    std::cout << "x: " << x << ", y: " << y << "\n";
}

Bishop::~Bishop(void) {}

std::vector<int> Bishop::getMoves() {
    std::vector<int> foo(1,1);
    return foo;
}

char Bishop::draw() {
    if (this->getHuman()) {
        return 'k';
    } else {
        return 'K';
    }
}
