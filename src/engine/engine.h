#ifndef ENGINE_H
#define ENGINE_H

// INCLUDES
#include <cctype>
#include <iostream>
#include <string>

void clrscr();
std::string toLowerEach(std::string input);
std::string stringPrompt(std::string message, bool lowercase);

#endif  // ENGINE_H