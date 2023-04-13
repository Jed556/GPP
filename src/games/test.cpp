#include <iostream>
#include <string>

int test() {
    std::string* cards;
    std::string suits[4] = {"♠", "♥", "♦", "♣"};
    std::string faces[13] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    int size = 0;
    cards = new std::string[52];
    for (const std::string& suit : suits) {
        for (const std::string& face : faces) {
            std::cout << suit << face << "\n";
            cards[size] = suit + face;
            size++;
        }
    }
    std::cout << "done";
    return 0;
}
