#ifndef PROMPT_H
#define PROMPT_H

#include <string>

std::string stringPrompt(std::string message, bool lowercase);
int intPrompt(std::string message);

#endif  // PROMPT_H