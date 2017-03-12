#include "Board.h"

Board::Board() {
    std::vector<int> row(6,0);
    for (int i = 0; i < 8; i++) {
        board.push_back(row);
    }

    //Piece *p = new King(0,1,false);
    //pieceList.push_back(p);
    /*pieceList.push_back(new Knight(1,0,false));
    pieceList.push_back(new Bishop(1,1,false));
    pieceList.push_back(new Rook(1,2,false));
    pieceList.push_back(new Rook(1,3,false));
    pieceList.push_back(new Bishop(1,4,false));
    pieceList.push_back(new Knight(1,5,false));

    pieceList.push_back(new King(7,4,true));
    pieceList.push_back(new Knight(1,0,true));
    pieceList.push_back(new Bishop(1,1,true));
    pieceList.push_back(new Rook(1,2,true));
    pieceList.push_back(new Rook(1,3,true));
    pieceList.push_back(new Bishop(1,4,true));
    pieceList.push_back(new Knight(1,5,true));*/

}

void Board::drawBoard() {
    for (std::size_t i = 0; i < pieceList.size(); i++) {
        
    }

    for (int i = 7; i >= 0; i--) {
        std::cout << i+1 << " ";
        for (int j = 5; j >= 0; j--) {
            char p = ' ';
            if (i == 3 && j == 4) p = 'B';

            if ((i+j)%2 ==0) {
                std::cout << "\033[1;46;37m " << p << " \033[0m";
            } else {
                std::cout << "\033[1;47;30m " << p << " \033[0m";
            }
        }
        std::cout << "\n";
    }
    std::cout << "   ";
    for (int i = 0; i < 6; i++) {
        switch (i) {
            case 0: std::cout << 'A';
                    break;
            case 1: std::cout << 'B';
                    break;
            case 2: std::cout << 'C';
                    break;
            case 3: std::cout << 'D';
                    break;
            case 4: std::cout << 'E';
                   break;  
            case 5: std::cout << 'F';
                   break;
            default: std::cout << 'Z';
        }
        std::cout << "  ";
    }
    std::cout << "\n";
}




