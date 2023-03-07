#include "games/games.h"  // HEADER

// INCLUDES
#include <cctype>
#include <iostream>
#include <string>

/**
 * @brief Clear screen
 */
void clrscr() {
    system("cls");
}

/**
 * @brief Convert each value to lowercase
 *
 * @param input String
 * @return Lowercase string
 */
std::string toLowerEach(std::string input) {
    std::string res;
    for (int i = 0; i < input.length(); i++)
        res[i] = tolower(input[i]);

    return res;
}

/**
 * @brief Handles Prompts
 *
 * @param message Message to display for prompt
 * @param lowercase Return input in lowercase
 * @return Input string
 */
std::string stringPrompt(std::string message, bool lowercase) {
    std::string answer;
    std::cout << message;
    std::cin >> answer;
    if (lowercase)
        for (char &c : answer)
            c = std::tolower(c);

    return answer;
}