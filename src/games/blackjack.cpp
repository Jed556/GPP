// HEADERS
#include <iostream>

#include "../engine/engine.h"
#include "games.h"

// CONFIG
int maxHand = 10;

// VARIABLES
std::string answer;
int playerMoney = 1000, bet, prize;
bool stand, hit;
bool restart;

// PROTOTYPES
void title();
void gameLoop();
bool exitPromptHandler(bool win, bool gameEnded);
void DisplayCards(Hand dealer, Hand player, bool isStand);

// GAME FUNCTIONS

void gameLoop() {
    // initialize game
    std::string suits[4] = {"♠", "♥", "♦", "♣"};
    std::string faces[13] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    Deck deck(suits, faces);

    // initialize hands
    Hand dealerHand(10), playerHand(10);
    dealerHand.drawCards(deck, 2);
    playerHand.drawCards(deck, 2);

    bool isGameOver = false;
    bool isPlayerTurn = true;
    bool isStand = false;

    // player turn loop
    while (!isGameOver && isPlayerTurn) {
        DisplayCards(dealerHand, playerHand, isStand);

        // player's turn
        if (playerHand.getTotalValue()[0] > 21) {
            std::cout << "Bust! You lost.\n\n";
            isGameOver = true;
            break;
        }

        hit = false;
        stand = false;

        while (!hit && !stand) {
            answer = stringPrompt("Do you want to hit or stand? ", true);
            if (answer == "hit") {
                playerHand.drawCards(deck, 1);
                hit = true;
            } else if (answer == "stand") {
                isPlayerTurn = false;
                isStand = true;
                stand = true;
            } else {
                std::cout << "Invalid input. Please enter 'hit' or 'stand'.\n";
            }
        }
    }

    // dealer's turn
    if (!isGameOver) {
        isStand = true;
        while (dealerHand.getTotalValue()[0] < 17) {
            dealerHand.drawCards(deck, 1);
        }
        DisplayCards(dealerHand, playerHand, isStand);

        if (dealerHand.getTotalValue()[0] > 21) {
            std::cout << "Dealer busts! You win!\n\n";
            prize = bet * 2;
            playerMoney += prize;
        } else if (dealerHand.getTotalValue()[0] > playerHand.getTotalValue()[0]) {
            std::cout << "Dealer wins!\n\n";
        } else if (dealerHand.getTotalValue()[0] == playerHand.getTotalValue()[0]) {
            std::cout << "It's a tie.\n\n";
            playerMoney += bet;
        } else {
            std::cout << "You win!\n\n";
            prize = bet * 2;
            playerMoney += prize;
        }

        isGameOver = !exitPromptHandler((prize > 0), true);
    }
}

/**
 * @brief Start Blackjack game
 *
 * @return Error status (int)
 */
int blackjack() {
    title();

    while (true) {
        std::cout << "You have $" << playerMoney << ".\n";
        bet = intPrompt("How much do you want to bet? ");

        if (bet > playerMoney) {
            std::cout << "You don't have enough money to bet $" << bet << ".\n\n";
            if (!exitPromptHandler(false, false))
                break;
        } else if (bet <= 0) {
            std::cout << "Invalid bet. Please enter a positive number.\n\n";
        } else {
            playerMoney -= bet;
            gameLoop();

            if (playerMoney <= 0) {
                std::cout << "You're out of money. Game over!\n";
                break;
            } else if (!restart) {
                break;
            }
        }
    }

    std::cout << "Thanks for playing!\n";
    return 0;
}

// SYSTEM FUNCTIONS

void title() {
    std::cout << "---------------------------- \n";
    std::cout << "    Welcome to Blackjack     \n";
    std::cout << "---------------------------- \n\n";
}

// Use this for restart / exit  check only
bool exitPromptHandler(bool win, bool gameEnded) {
    std::string message;
    if (gameEnded)
        switch (win) {
            case true:
                message = "Do you like to play again? ";
                break;
            case false:
                message = "Would you like to try again? ";
                break;
        }
    else
        message = "Would you like to play? ";

    answer = stringPrompt(message, true);

    const std::string arrTrue[] = {"yes", "y", "naur", "yeah", "yep"};  // Responses for true
    const std::string arrFalse[] = {"no", "n", "naur", "nah", "nope"};  // Responses for false
    const int numArrTrue = sizeof(arrTrue) / sizeof(arrTrue[0]);        // Number of elements in array
    const int numArrFalse = sizeof(arrFalse) / sizeof(arrFalse[0]);     // Number of elements in array

    if (numArrTrue == numArrFalse) {
        for (int i = 0; i < numArrTrue; i++)  // Computing shortcut
            if (answer == arrTrue[i])
                return true;
            else if (answer == arrFalse[i])
                return false;
    } else {
        for (int i = 0; i < numArrTrue; i++)  // Long version
            if (answer == arrTrue[i])
                return true;

        for (int i = 0; i < numArrFalse; i++)
            if (answer == arrFalse[i])
                return false;
    }

    message = "I didn't catch that. " + message;
    return exitPromptHandler(win, gameEnded);
}

// GAME FUNCTIONS

void DisplayCards(Hand dealer, Hand player, bool isStand) {
    std::cout << "Dealer's cards:\n\n";
    if (isStand) {
        dealer.printCards(true);
        std::cout << "Dealer's card count: ";
        std::cout << player.getTotalValue()[0] << (player.getTotalValue()[1] > 0 ? " or " + std::to_string(player.getTotalValue()[1]) : "") << "\n\n";
    } else {
        dealer.getCard(0);
        std::cout << "| " << dealer.getCard(0) << " | ? |" << std::endl;
    }
    std::cout << "\n\n";

    std::cout << "Your cards:\n\n";
    player.printCards(true);
    std::cout << "\n\n";

    std::cout << "Your card count: ";
    std::cout << player.getTotalValue()[0] << (player.getTotalValue()[1] > 0 ? " or " + std::to_string(player.getTotalValue()[1]) : "") << "\n\n";
}