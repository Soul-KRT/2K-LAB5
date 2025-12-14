#include <locale>
#include <iostream>
#include "Game.h"

int main() {
    setlocale(LC_ALL, "Russian");

    Game game;
    int again = 1;
    while (again == 1) {
        game.playRound();
        std::cout << "Сыграть ещё? (1/2): ";
        std::cin >> again;
    }
    return 0;
}
