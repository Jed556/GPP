#include <iostream>
#include <string>

#include "engine/engine.h"
#include "games/games.h"

Engine engine;

int main() {
Start:
    std::string message;
    std::string games[] = {"Blackjack (WIP)", "Multiple Choice", "Exit"};

    while (true) {
        // Game selection
        clrscr();
        std::cout << "GPP (C++ Terminal Game Engine)\n"
                  << "by Jed556 | version: " << engine.version() << "\n\n";

        message = "Select index: ";
        for (int i = 0; i < sizeof(games) / sizeof(games[0]); i++)
            std::cout << "[" << i + 1 << "] " << games[i] << "\n";
        int answer = intPrompt(message);

        switch (answer) {
            case 1:
                blackjack();
                break;
            case 2:
                multiplechoice();
                break;
            case 3:
                return 0;
            default:
                message = "I didn't catch that.";
                continue;
        }

        while (true) {
            clrscr();
            message = "Do you like to restart launcher? ";
            std::string answer = stringPrompt(message, true);

            // Can be added to game engine (soon)
            const std::string arrTrue[] = {"yes", "y", "yeah", "yep"};        // Responses for true
            const std::string arrFalse[] = {"no", "n", "nah", "nope"};        // Responses for false
            const int sizeArrTrue = sizeof(arrTrue) / sizeof(arrTrue[0]);     // Number of elements in array
            const int sizeArrFalse = sizeof(arrFalse) / sizeof(arrFalse[0]);  // Number of elements in array

            if (sizeArrTrue == sizeArrFalse) {
                for (int i = 0; i < sizeArrTrue; i++)  // Computing shortcut
                    if (answer == arrTrue[i])
                        goto Start;
                    else if (answer == arrFalse[i])
                        return 0;
            } else {
                for (int i = 0; i < sizeArrTrue; i++)  // Long version
                    if (answer == arrTrue[i])
                        goto Start;

                for (int i = 0; i < sizeArrFalse; i++)
                    if (answer == arrFalse[i])
                        return 0;
            }

            message = "I didn't catch that. " + message;
        }
    }
}