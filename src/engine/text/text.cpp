#include "../text.h"

#include <string>

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
 * @brief Convert each value to uppercase
 *
 * @param input String
 * @return Uppercase string
 */
std::string toUpperEach(std::string input) {
    std::string res;
    for (int i = 0; i < input.length(); i++)
        res[i] = toupper(input[i]);

    return res;
}