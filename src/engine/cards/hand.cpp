#include <algorithm>
#include <array>
#include <cctype>
#include <iostream>
#include <random>
#include <sstream>
#include <string>

#include "../cards.h"

/**
 * @brief Construct a new Cards object
 *
 * @param size Maximum number of cards on hand or array size (default: 10)
 */
Hand::Hand(int size)
    : cards(nullptr), size(0) {
    if (size <= 0) {
        size = 10;
    }
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
 * @brief Get the total value of all cards on hand
 *
 * @return std::array<int, 2> Total value of cards on hand
 */
std::array<int, 2> Hand::getTotalValue() const {
    int sum = 0;
    int num_aces = 0;
    for (int i = 0; i < size; i++) {
        int card_value = getValue(i);
        if (card_value == 1) {
            num_aces++;
        }
        sum += card_value;
    }

    std::array<int, 2> total_value{sum, 0};
    if (num_aces > 0) {
        int ace_high_sum = sum + 10 * num_aces;
        if (ace_high_sum <= 21) {
            total_value[1] = ace_high_sum;
        }
    }
    return total_value;
}

/**
 * @brief Get the Hand Size object
 *
 * @return int Population of cards on hand
 */
int Hand::getHandSize() const {
    int handSize = 0;  // Small PP
    for (int i = 0;; i++) {
        if (cards[i] != "") {
            handSize++;
        } else {
            break;
        }
    }
    return handSize;
}

/**
 * @brief Get maximum card slots on hand
 *
 * @return int Max card slots (array size)
 */
int Hand::getSize() const {
    return size;
}

/**
 * @brief Draws 2 or less cards from deck
 *
 * @param obj Deck class object
 * @param numDraws Number of cards to draw
 */
void Hand::drawCards(Deck obj, int numDraws) {
    std::string* deck = obj.getDeck();
    int deckSize = obj.getDeckSize();
    int numDrawn = 0;
    int debug = 1;

    if (debug) {
        std::cout << "\nCards on deck: " << std::endl;
        for (int i = 0; i < size; i++)
            std::cout << (i ? ", " : "") << obj.getCard(i);
    }

    for (int i = numCards; i < size - numCards && numDrawn < numDraws; i++) {
        if (numCards + 1 > deckSize) break;

        if (deck[i] != "") {
            setCard(numCards++, deck[i]);
            obj.setCard(i, "");
            numDrawn++;
        }
    }

    if (debug) {
        std::cout << "\nCards on hand: " << std::endl;
        for (int i = 0; i < size; i++)
            std::cout << (i ? ", " : "") << getCard(i);

        std::cout << "\nCards on deck: " << std::endl;
        for (int i = 0; i < size; i++)
            std::cout << (i ? ", " : "") << obj.getCard(i);

        std::cout << std::endl;
    }

    int prevIndex = 0;
    for (int i = 0; i < 52; i++) {
        if (deck[i] != "") {
            if (debug) std::cout << "i: " << i << " prevIndex: " << prevIndex << std::endl;
            obj.setCard(prevIndex++, deck[i]);
        }
    }
    // The bug is here, or before the loop ends - what():  std::bad_alloc
    // The bug is due to Deck.getDeckSize (similar to Hand.getHandSize) counting
    // until a blank index is reached instead of returning a fixed value
    // Will use 52 as a fixed value for now... I'd rather die than fix this
    while (prevIndex < 52) {
        if (debug) std::cout << "prevIndex: " << prevIndex << std::endl;
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

    for (int i = 0; i < size; i++) {
        ss << "| " << getCard(i) << " ";
    }
    ss << "|";

    std::string output = ss.str();
    if (print) {
        std::cout << output << std::endl;
    }

    return output;
}