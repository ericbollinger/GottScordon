#include "Move.h"

Move::Move(int f, int fp, int t, int tp, bool c) {
    from = f;
    pieceFrom = fp;
    to = t;
    pieceTo = tp;
    isCapture = c;
}
