#include <algorithm>
#include <array>
#include <cctype>
#include <iostream>
#include <random>
#include <sstream>
#include <string>

#include "cards.h"

std::string suits[4] = {"♠", "♥", "♦", "♣"};
std::string faces[13] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};

/**
 * @brief Construct a new Deck object
 */
Deck::Deck() {
    for (const std::string& suit : suits) {
        for (const std::string& face : faces) {
            cards[size] = suit + face;
            size++;
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
 * @return int Max card slots (array size)
 */
int Deck::getSize() const {
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