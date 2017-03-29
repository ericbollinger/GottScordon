#include "Move.h"

Move::Move(int f, int pf, int t, int pt, bool c) {
    from = f;
    pieceFrom = pf;
    to = t;
    pieceTo = pt;
    isCapture = c;
}

int Move::getFrom() { 
    return from;
}

void Move::setFrom(int f) {
    from = f;
}

int Move::getPieceFrom() {
    return pieceFrom;
}

void Move::setPieceFrom(int pf) {
    pieceFrom = pf;
}

int Move::getTo() {
    return to;
}

void Move::setTo(int t) {
    to = t;
}

int Move::getPieceTo() {
    return pieceTo;
}

void Move::setPieceTo(int pt) {
    pieceTo = pt;
}

bool Move::getCapture() {
    return isCapture;
}

void Move::setCapture(bool c) {
    isCapture = c;
}
