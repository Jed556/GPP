#include <string>

#include "games/games.h"
#include "engine/engine.h"

int main() {
Start:
    std::string answer;
    std::string message;

    while (true) {
        blackjack();

        while (true) {
            clrscr();
            message = "Do you like to restart launcher? ";
            answer = stringPrompt(message, true);

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