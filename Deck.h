#pragma once
#include <vector>
#include <random>
#include <algorithm>
#include "Card.h"

class Deck {
    std::vector<Card> cards;
    size_t index;
public:
    Deck();

    void shuffle();
    Card deal();

    bool empty() const { return index >= cards.size(); }
    int  sizeLeft() const { return static_cast<int>(cards.size() - index); }
};
