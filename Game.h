#pragma once
#include <array>
#include "Deck.h"
#include "Dealer.h"
#include "HumanPlayer.h"

class Game {
    std::array<Deck, 4> decks;
    Dealer dealer;
    HumanPlayer player;
public:
    Game();

    void playRound();   

private:
    Deck& chooseDeck();
    void printDeckSizes();
};
