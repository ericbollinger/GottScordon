#include <iostream>
#include <string>
#include <stdlib.h>

class Move {

    private:
        int from;
        int pieceFrom;
        int to;
        int pieceTo;
        bool isCapture;

    public:
        Move(int from, int pieceFrom, int to, int pieceTo, bool isCapture);
        int getFrom();
        void setFrom(int f);
        int getPieceFrom();
        void setPieceFrom(int p);
        int getTo();
        void setTo(int t);
        int getPieceTo();
        void setPieceTo(int p);
        bool getCapture();
        int setCapture(bool c);

};
