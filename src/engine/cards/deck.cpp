#include <algorithm>
#include <array>
#include <cctype>
#include <iostream>
#include <random>
#include <sstream>
#include <string>

#include "../cards.h"

/**
 * @brief Construct a new Deck object
 */
Deck::Deck(std::string* suits, std::string* faces) {
    size = sizeof(suits) / sizeof(suits[0]) * sizeof(faces) / sizeof(faces[0]);
    cards = new std::string[size];
    size_t index = 0;
    for (size_t i = 0; i < sizeof(suits) / sizeof(suits[0]); i++) {
        for (size_t j = 0; j < sizeof(faces) / sizeof(faces[0]); j++) {
            cards[index++] = suits[i] + faces[j];
        }
    }
    shuffle();
}

/**
 * @brief Free memory allocated for cards on deck
 */
Deck::~Deck() {
    delete[] cards;
}

/**
 * @brief Change or add card into deck
 *
 * @param index Position of card on deck (array index)
 * @param value Value of the card
 */
void Deck::setCard(int index, std::string value) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of bounds");
    }
    cards[index] = value;
}

/**
 * @brief Set card in index to null
 *
 * @param index Position of card on deck (array index)
 */
void Deck::setNull(int index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of bounds");
    }
    cards[index] = "";
}

/**
 * @brief Get a card from deck
 *
 * @param index Position of card on deck (array index)
 * @return std::string Card from deck
 */
std::string Deck::getCard(int index) const {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of bounds");
    }
    return cards[index];
}

/**
 * @brief Get all cards on deck
 *
 * @return std::string* All cards on deck
 */
std::string* Deck::getDeck() const {
    return cards;
}

/**
 * @brief Get the populated size of the deck
 *
 * @return int Size of the deck
 */
int Deck::getDeckSize() const {
    int deckSize = 0;  // Small PP
    for (int i = 0;; i++) {
        if (cards[i] != "") {
            deckSize++;
        } else {
            break;
        }
    }
    return deckSize;
}

/**
 * @brief Get maximum card slots on hand
 *
 * @return unsigned int Max card slots (array size)
 */
size_t Deck::getSize() const {
    return size;
}

/**
 * @brief Shuffle all cards on deck
 *
 */
void Deck::shuffle() const {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(cards, cards + size, g);
}

/**
 * @brief Get a formatted string of all cards on deck (optional: print to console)
 *
 * @param print Whether to print to console or not
 * @return std::string All cards on deck (formatted string)
 */
std::string Deck::printCards(bool print) const {
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