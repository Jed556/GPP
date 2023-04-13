#include <cstdlib>  // for std::rand and std::srand
#include <ctime>    // for std::time
#include <iostream>

#include "../engine/engine.h"
#include "games.h"

int multiplechoice() {
    std::string category1[][2] = {
        {"What is the capital of Canada?", "Ottawa"},
        {"What is the largest country in South America?", "Brazil"},
        {"What is the smallest continent?", "Australia"},
        {"What is the highest mountain in North America?", "Denali"},
        {"What is the longest river in Asia?", "Yangtze"}};
    std::string category2[][2] = {
        {"What is the name of the famous monument in India?", "Taj Mahal"},
        {"What is the tallest building in the world?", "Burj Khalifa"},
        {"What is the name of the famous wall in China?", "Great Wall of China"},
        {"What is the name of the famous statue in New York City?", "Statue of Liberty"},
        {"What is the name of the famous tower in France?", "Eiffel Tower"}};
    std::string category3[][2] = {
        {"What is the name of the famous Italian dish with tomato sauce and cheese?", "Pizza"},
        {"What is the name of the Japanese dish consisting of rice, raw fish, and vegetables?", "Sushi"},
        {"What is the name of the Mexican dish consisting of a tortilla filled with beans, meat, and cheese?", "Burrito"},
        {"What is the name of the French dish consisting of snails in garlic butter?", "Escargots"},
        {"What is the name of the Chinese dish consisting of thin noodles served with vegetables and meat?", "Chow Mein"}};

    MultiChoiceQs mcq_category1(5, category1);
    MultiChoiceQs mcq_category2(5, category2);
    MultiChoiceQs mcq_category3(5, category3);

    int totalSize = mcq_category1.getSize() + mcq_category2.getSize() + mcq_category3.getSize();

    int overflow = 0;
    int count1 = 0, count2 = 0, count3 = 0;
    for (int i = 0; i < totalSize; i++) {
        if (overflow) {
            overflow = 0;
        } else {
            std::cout << "\nQuestion " << i + 1 << " of " << totalSize << "\n";
        }

        int category = rand() % 3 + 1;

        switch (category) {
            case 1:
                if (count1 < mcq_category1.getSize())
                    mcq_category1.askQuestion(count1++, 4);
                else
                    overflow = 1;
                break;

            case 2:
                if (count2 < mcq_category2.getSize())
                    mcq_category2.askQuestion(count2++, 4);
                else
                    overflow = 1;
                break;

            case 3:
                if (count3 < mcq_category3.getSize())
                    mcq_category3.askQuestion(count3++, 4);
                else
                    overflow = 1;
                break;
        }

        if (overflow) --i;
    }

    return 0;
}