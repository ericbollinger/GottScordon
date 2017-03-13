#include "gottscordon.h"

int main() {
    int whoGoesFirst;
    std::cout << "If you would like to go first, please enter '1'. If you would like the computer to go first, please enter '2'.\n";
    std::cin >> whoGoesFirst;
    if (whoGoesFirst == 1) {
        std::cout << "Human first!\n";
    } else {
        std::cout << "Computer first!\n";
    }

    Game *game = new Game();

    time_t end = time(NULL) + 5;
    int n = 0;
    while (time(NULL) < end) {
        n++;
        game->showAllHumanMoves();   
        std::cout << n << "\n";
    }

    return 1;
}
