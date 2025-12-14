#pragma once
#include "Player.h"

class Dealer : public Player {
public:
    Dealer() : Player("Дилер") {}

    bool wantsCard(int currentTotal) override {
        // базовое правило: берём до 17 включительно
        return currentTotal < 17;
    }
};
