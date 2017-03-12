#include "Piece.h"

Piece::Piece(int x, int y, bool human, int weight) {
    this->x = x;
    this->y = y;
    this->human = human;
    this->weight = weight;
}

Piece::~Piece(void) {}

void Piece::morph() {

}

int Piece::getX() {
    return x;
}

void Piece::setX(int x) {
    this->x = x;
}

int Piece::getY() {
    return y;
}

void Piece::setY(int y) {
    this->y = y;
}

bool Piece::getHuman() {
    return human;
}

int Piece::getWeight() {
    return weight;
}
