#pragma once
#include <iostream>

enum class Rank {
    Two = 2, Three, Four, Five, Six, Seven,
    Eight, Nine, Ten, Jack, Queen, King, Ace
};

enum class Suit { Spades }; // одномастный вариант

class Card {
    Rank rank;
    Suit suit;
public:
    Card(Rank r = Rank::Two, Suit s = Suit::Spades)
        : rank(r), suit(s) {
    }

    int  value() const;
    Rank getRank() const { return rank; }

    friend std::ostream& operator<<(std::ostream& os, const Card& c);
};
