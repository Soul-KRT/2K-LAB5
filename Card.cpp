#include "Card.h"
#include <string>

int Card::value() const {
    switch (rank) {
    case Rank::Two:   return 2;
    case Rank::Three: return 3;
    case Rank::Four:  return 4;
    case Rank::Five:  return 5;
    case Rank::Six:   return 6;
    case Rank::Seven: return 7;
    case Rank::Eight: return 8;
    case Rank::Nine:  return 9;
    case Rank::Ten:
    case Rank::Jack:
    case Rank::Queen:
    case Rank::King:  return 10;
    case Rank::Ace:   return 11;
    }
    return 0;
}

std::ostream& operator<<(std::ostream& os, const Card& c) {
    std::string rankStr;
    switch (c.getRank()) {
    case Rank::Two:   rankStr = "2";  break;
    case Rank::Three: rankStr = "3";  break;
    case Rank::Four:  rankStr = "4";  break;
    case Rank::Five:  rankStr = "5";  break;
    case Rank::Six:   rankStr = "6";  break;
    case Rank::Seven: rankStr = "7";  break;
    case Rank::Eight: rankStr = "8";  break;
    case Rank::Nine:  rankStr = "9";  break;
    case Rank::Ten:   rankStr = "10"; break;
    case Rank::Jack:  rankStr = "J";  break;
    case Rank::Queen: rankStr = "Q";  break;
    case Rank::King:  rankStr = "K";  break;
    case Rank::Ace:   rankStr = "A";  break;
    }

    char suitChar = '\x06'; // пики в win-консоли
    os << rankStr << suitChar;
    return os;
}
