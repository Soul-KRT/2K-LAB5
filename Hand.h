#pragma once
#include <vector>
#include "Card.h"
#include "BustException.h"

class Hand {
    std::vector<Card> cards;
public:
    void addCard(const Card& c) { cards.push_back(c); }

    int  total() const;
    void clear() { cards.clear(); }

    const std::vector<Card>& getCards() const { return cards; }
};
