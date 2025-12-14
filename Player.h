#pragma once
#include <string>
#include "Hand.h"

class Player {
protected:
    std::string name;
    Hand hand;
public:
    Player(const std::string& n) : name(n) {}
    virtual ~Player() = default;

    virtual void takeCard(const Card& c) { hand.addCard(c); }
    virtual bool wantsCard(int currentTotal) = 0;

    Hand& getHand() { return hand; }
    const std::string& getName() const { return name; }
};
