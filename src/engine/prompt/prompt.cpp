#include "prompt.h"

#include <iostream>
#include <string>

/**
 * @brief Handles String Prompts
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

/**
 * @brief Handles Integer Prompts
 *
 * @param message Message to display for prompt
 * @return Input integer
 */
int intPrompt(std::string message) {
    int answer;
    std::cout << message;
    std::cin >> answer;

    return answer;
}