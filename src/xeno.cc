#include "xeno.h"

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
        game->makeComputerMove();
        game->checkForGameEnd();
        normalTurnSequence = 1;
    }

    return 1;
}
