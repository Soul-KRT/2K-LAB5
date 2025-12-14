#include "Hand.h"

int Hand::total() const {
    int sum = 0;
    int aces = 0;
    for (auto& c : cards) {
        sum += c.value();
        if (c.getRank() == Rank::Ace) ++aces;
    }
    while (sum > 21 && aces > 0) {
        sum -= 10;
        --aces;
    }
    if (sum > 21)
        throw BustException();
    return sum;
}
