#include "../engine/engine.h"
#include "games.h"

int multiplechoice() {
    std::string qa[][2] = {
        {"What is the capital of France?", "Paris"},
        {"What is the largest country in the world?", "Russia"},
        {"What is the highest mountain in the world?", "Mount Everest"}};
    MultiChoiceQs mcq(3, qa);

    for (int i = 0; i < mcq.getSize(); i++) {
        mcq.generateChoices(i, 4);
        mcq.askQuestion(i);
    }

    return 0;
}