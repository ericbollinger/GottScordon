#include "King.h"

King::King(int x, int y, bool human) : Piece::Piece(x, y, human, 99) {
    std::cout << "x: " << x << ", y: " << y << "\n";
}

King::~King(void) {}

std::vector<int> King::getMoves() {
    std::vector<int> foo(1,1);
    return foo;
}

char King::draw() {
    if (this->getHuman()) {
        return 'k';
    } else {
        return 'K';
    }
}
