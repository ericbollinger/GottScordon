#include "Knight.h"

Knight::Knight(int x, int y, bool human) : Piece::Piece(x, y, human, 99) {
    std::cout << "x: " << x << ", y: " << y << "\n";
}

Knight::~Knight(void) {}

std::vector<int> Knight::getMoves() {
    std::vector<int> foo(1,1);
    return foo;
}

char Knight::draw() {
    if (this->getHuman()) {
        return 'k';
    } else {
        return 'K';
    }
}
