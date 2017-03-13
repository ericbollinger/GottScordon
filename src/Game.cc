#include "Game.h"

Game::Game() {
    board = Board();
    board.drawBoard();
    didSomeoneWin = false;
}

int Game::colToInt(char col) {
    switch (col) {
        case 'A': return 0;
        case 'B': return 1;
        case 'C': return 2;
        case 'D': return 3;
        case 'E': return 4;
        case 'F': return 5;
        default:  return -1;
    }
}

char Game::colToChar(int col) {
    return "ABCDEF"[col];
}

int Game::decodeSpace(std::string space) {
    char y = space.at(0);
    char x = space.at(1);

    int xInt = colToInt(x);
    int yInt = y - '0';

    return (yInt * 8) + xInt;
}

std::string Game::encodeSpace(int space) {
    int x = space % 6;
    int y = space / 6 + 1;

    std::stringstream result;
    result << "ABCDEF"[x];
    result << y;
    return result.str();
}

void Game::showAllHumanMoves() {
    std::vector<int> moves = board.getHumanMoves();
    for (size_t i = 0; i < moves.size(); i+= 2) {
        //std::cout << encodeSpace(moves[i]) << "->" << encodeSpace(moves[i+1]) << "\n";
    }
}
