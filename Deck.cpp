#include "Deck.h"

Deck::Deck() : index(0) {
    // одномастная "четверная" колода: 4 одинаковых масти
    for (int r = static_cast<int>(Rank::Two);
        r <= static_cast<int>(Rank::Ace); ++r) {
        for (int i = 0; i < 4; ++i)
            cards.emplace_back(static_cast<Rank>(r), Suit::Spades);
    }
}

void Deck::shuffle() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(cards.begin(), cards.end(), gen);
    index = 0;
}

Card Deck::deal() {
    if (empty())
        shuffle();
    return cards[index++];
}
