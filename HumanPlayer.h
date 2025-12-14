#pragma once
#include "Player.h"
#include <iostream>

class HumanPlayer : public Player {
public:
    HumanPlayer(const std::string& n) : Player(n) {}

    bool wantsCard(int currentTotal) override {
        std::cout << "Вы, у вас " << currentTotal
            << ". Взять карту? (1 - хватит, 2 - ещё): ";
        int ch;
        std::cin >> ch;
        return ch == 2;
    }
};
