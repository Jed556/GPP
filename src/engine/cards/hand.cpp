#include <algorithm>
#include <array>
#include <cctype>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <vector>

#include "../cards.h"

/**
 * @brief Construct a new Cards object
 *
 * @param size Maximum number of cards on hand or array size (default: 10)
 */
Hand::Hand(size_t size)
    : cards(nullptr), size(0) {
    if (size <= 0) size = 10;
    cards = new std::string[size];
    this->size = size;
}

/**
 * @brief Free memory allocated for cards on hand
 */
Hand::~Hand() {
    delete[] cards;
}

/**
 * @brief Change or add card into hand
 *
 * @param index Position of card on hand (array index)
 * @param value Value of the card
 */
void Hand::setCard(int index, std::string value) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of bounds");
    }
    cards[index] = value;
}

/**
 * @brief Set card in index to null
 *
 * @param index Position of card on hand (array index)
 */
void Hand::setNull(int index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of bounds");
    }
    cards[index] = "";
}

/**
 * @brief Get a card from hand
 *
 * @param index Position of card on hand (array index)
 * @return std::string Card from hand
 */
std::string Hand::getCard(int index) const {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of bounds");
    }
    return cards[index];
}

/**
 * @brief Get all cards on hand
 *
 * @return std::string* All cards on hand
 */
std::string* Hand::getHand() const {
    return cards;
}

/**
 * @brief Get card value
 *
 * @param index Position of card on hand (array index)
 * @return int
 */
int Hand::getValue(int index) const {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of bounds");
    }
    std::string card = cards[index];
    if (card[0] == 'A') {
        return 1;
    } else if (card[0] >= '2' && card[0] <= '9') {
        return card[0] - '0';
    } else {
        return 10;
    }
}

/**
 * @brief Generate all possible hand combinations with aces
 *
 * @param i Index of current card to consider
 * @param sum Current sum of cards
 * @param num_aces Number of aces in hand
 * @param results Array of possible hand combinations
 */
void Hand::generateTotalValues(int i, int sum, int num_aces, std::vector<int>& results) const {
    if (i == getHandSize()) {
        results.push_back(sum);
        return;
    }

    int card_value = getValue(i);
    if (card_value == 1) {
        num_aces++;
        generateTotalValues(i + 1, sum + 1, num_aces, results);
        if (num_aces > 1) {
            generateTotalValues(i + 1, sum + 11, num_aces, results);
        }
        num_aces--;
    } else {
        generateTotalValues(i + 1, sum + card_value, num_aces, results);
    }
}

/**
 * @brief Get all possible hand combinations with aces
 *
 * @return std::vector<int> Array of possible hand combinations
 */
std::vector<int> Hand::getTotalValues() const {
    std::vector<int> results;
    generateTotalValues(0, 0, 0, results);
    return results;
}

/**
 * @brief Get the Hand Size object
 *
 * @return int Population of cards on hand
 */
int Hand::getHandSize() const {
    int handSize = 0;
    while (cards[handSize] != "" && handSize < size) handSize++;

    return handSize;
}

/**
 * @brief Get maximum card slots on hand
 *
 * @return int Max card slots (array size)
 */
size_t Hand::getSize() const {
    return size;
}

/**
 * @brief Draws cards from deck
 *
 * @param obj Deck class object
 * @param numDraws Number of cards to draw
 */
void Hand::drawCards(Deck& obj, int numDraws) {
    std::string* deck = obj.getDeck();
    int deckSize = obj.getSize();
    int numDrawn = 0;

    for (int i = numCards; i < size - numCards && numDrawn < numDraws; i++) {
        if (numCards + 1 > deckSize) break;

        if (deck[i] != "") {
            setCard(numCards++, deck[i]);
            obj.setCard(i, "");
            numDrawn++;
        }
    }

    int prevIndex = 0;
    for (int i = 0; i < deckSize; i++) {
        if (deck[i] != "") {
            obj.setCard(prevIndex++, deck[i]);
        }
    }

    while (prevIndex < deckSize) {
        obj.setCard(prevIndex++, "");
    }
}

/**
 * @brief Get a formatted string of all cards on hand (optional: print to console)
 *
 * @param print Whether to print to console or not
 * @return std::string All cards on hand (formatted string)
 */
std::string Hand::printCards(bool print) const {
    std::stringstream ss;

    for (int i = 0; i < getHandSize(); i++) {
        ss << "| " << getCard(i) << " ";
    }
    ss << "|";

    std::string output = ss.str();
    if (print) {
        std::cout << output;
    }

    return output;
}

/**
 * @brief Print all possible hand value combinations with aces
 *
 * @param print If true, print the combinations to stdout
 * @return std::string Formatted string of all possible hand value combinations
 */
std::string Hand::printTotalValues(bool print) const {
    std::vector<int> values = getTotalValues();

    std::stringstream ss;
    for (int i = 0; i < values.size(); i++) {
        ss << (i > 0 ? ", " : "") << values[i];
    }

    if (print) {
        std::cout << ss.str();
    }

    return ss.str();
}
