#include "gottscordon.h"

int colToInt(char col) {
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

char colToStr(int col) {
    return "ABCDEF"[col];
}

std::vector<int> decodeMove(std::string mov) {
    char fromYInt = mov.at(0);
    char fromXStr = mov.at(1);
    char toYInt = mov.at(2);
    char toXStr = mov.at(3);

    int tmp;
    std::vector<int> result;
    tmp = fromYInt - '0';
    result.push_back(tmp);
    result.push_back(colToInt(fromXStr));
    tmp = toYInt - '0';
    result.push_back(tmp);
    result.push_back(colToInt(toXStr));
    return result;
}

std::string encodeMove(std::vector<int> mov) {
    std::stringstream result;
    result << mov[0];
    result << colToStr(mov[1]);
    result << mov[2];
    result << colToStr(mov[3]);
    return result.str();
}

int main() {
    // Ask whether player would like to go first
    Board *b = new Board();
    b->drawBoard();

    return 1;
}
