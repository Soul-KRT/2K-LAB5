#include "Game.h"
#include <iostream>

static int g_balance = 10000;

Game::Game()
    : player("Игрок")
{
    for (auto& d : decks)
        d.shuffle();
}

Deck& Game::chooseDeck() {
    for (auto& d : decks)
        if (!d.empty())
            return d;
    return decks[0];
}

void Game::printDeckSizes() {
    std::cout << "Колоды: ";
    for (const auto& d : decks)
        std::cout << "[" << d.sizeLeft() << "] ";
    std::cout << "\n";
}

void Game::playRound() {
    int bet = 0;
    std::cout << "Ваша ставка? ";
    std::cin >> bet;
    if (bet <= 0 || bet > g_balance) {
        std::cout << "Неверная ставка.\n";
        return;
    }

    player.getHand().clear();
    dealer.getHand().clear();

    // раздача: игрок, дилер, игрок, дилер
    Deck& d0 = chooseDeck();
    player.takeCard(d0.deal());

    Deck& d1 = chooseDeck();
    dealer.takeCard(d1.deal());

    Deck& d2 = chooseDeck();
    player.takeCard(d2.deal());

    Deck& d3 = chooseDeck();
    dealer.takeCard(d3.deal());

    printDeckSizes();

    std::cout << "Дилер: "
        << dealer.getHand().getCards()[0]
        << " ??\n";

    std::cout << "Вы: ";
    for (auto const& c : player.getHand().getCards())
        std::cout << c << " ";
    std::cout << "\n";

    bool playerBust = false;

    while (true) {
        int total;
        try {
            total = player.getHand().total();
        }
        catch (const BustException&) {
            std::cout << "Перебор у игрока!\n";
            playerBust = true;
            break;
        }

        std::cout << "1. Хватит\n2. Еще\n";
        int choice;
        std::cin >> choice;

        if (choice == 1) break;
        else if (choice == 2) {
            Deck& d = chooseDeck();
            Card c = d.deal();
            player.takeCard(c);
            printDeckSizes();
            std::cout << "Вы взяли: " << c << "\n";

            std::cout << "Вы: ";
            for (auto const& k : player.getHand().getCards())
                std::cout << k << " ";
            std::cout << "\n";
        }
    }

    if (playerBust) {
        g_balance -= bet;
        std::cout << "Вы проиграли.\n";
        std::cout << "Вы потеряли: " << bet
            << ". Всего: " << g_balance << ".\n";
        return;
    }

    // ход дилера
    std::cout << "Колоды: ";
    printDeckSizes();

    std::cout << "Дилер: ";
    for (auto const& c : dealer.getHand().getCards())
        std::cout << c << " ";
    std::cout << "\n";

    try {
        while (dealer.wantsCard(dealer.getHand().total())) {
            Deck& d = chooseDeck();
            Card c = d.deal();
            dealer.takeCard(c);
            std::cout << "Дилер берет: " << c << "\n";
        }
    }
    catch (const BustException&) {
        std::cout << "Перебор у дилера!\n";
        std::cout << "Поздравляем! Вы выиграли!\n";
        g_balance += bet;
        std::cout << "Ваш выигрыш: " << bet
            << ". Всего: " << g_balance << ".\n";
        return;
    }

    int pt, dt;
    try {
        pt = player.getHand().total();
        dt = dealer.getHand().total();
    }
    catch (const BustException&) {
        std::cout << "Ошибка подсчёта.\n";
        return;
    }

    if (pt > dt) {
        std::cout << "Поздравляем! Вы выиграли!\n";
        g_balance += bet;
        std::cout << "Ваш выигрыш: " << bet
            << ". Всего: " << g_balance << ".\n";
    }
    else if (pt < dt) {
        std::cout << "Вы проиграли.\n";
        g_balance -= bet;
        std::cout << "Вы потеряли: " << bet
            << ". Всего: " << g_balance << ".\n";
    }
    else {
        std::cout << "Ровно (ничья).\n";
        std::cout << "Всего: " << g_balance << ".\n";
    }
}
