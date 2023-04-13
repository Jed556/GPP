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

/**
 * @brief Start Blackjack game
 *
 * @return Error status (int)
 */
int blackjack() {
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