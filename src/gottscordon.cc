#include "gottscordon.h"

int main() {
    int normalTurnSequence;
    std::cout << "If you would like to go first, please enter '1'. If you would like the computer to go first, please enter '2'.\n";
    std::cin >> normalTurnSequence;

    Game *game = new Game();

    for(;;) {
        if (normalTurnSequence == 1) {
            game->inputMove();
            game->checkForGameEnd();
        }
        time_t start = time(NULL);
        game->makeComputerMove();
        time_t end = time(NULL);
        std::cout << end-start << " seconds\n";
        game->checkForGameEnd();
        normalTurnSequence = 1;
    }

    return 1;
}
