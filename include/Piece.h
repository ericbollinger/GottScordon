#include <iostream>
#include <vector>
#include <string>

class Piece {
    
    private:
        int x;
        int y;
        bool human;
        int weight;

    public:
        void morph();
        int getX();
        void setX(int x);
        int getY();
        void setY(int y);
        int getWeight();
        bool getHuman();
        virtual char draw() = 0;
        Piece(int x, int y, bool human, int weight);
        ~Piece();
};
