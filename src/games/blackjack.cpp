// HEADERS
#include "games.h"

// INCLUDES
#include <algorithm>
#include <array>
#include <cctype>
#include <iostream>
#include <random>
#include <sstream>
#include <string>

// CONFIG
int maxHand = 10;

// VARIABLES
std::string answer;
int playerMoney = 1000, bet, prize;
bool stand, hit;
bool restart;

// CARD STRUCTURE

/**
 * @brief Deck structure
 */
class Deck {
   private:
    std::string suits[4] = {"♠", "♥", "♦", "♣"};
    std::string faces[13] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    std::string* cards;
    int size = 0;

   public:
    /**
     * @brief Construct a new Deck object
     */
    Deck() {
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
    ~Deck() {
        delete[] cards;
    }

    /**
     * @brief Change or add card into deck
     *
     * @param index Position of card on deck (array index)
     * @param value Value of the card
     */
    void setCard(int index, std::string value) {
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
    void setNull(int index) {
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
    std::string getCard(int index) const {
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
    std::string* getDeck() const {
        return cards;
    }

    /**
     * @brief Get the populated size of the deck
     *
     * @return int Size of the deck
     */
    int getDeckSize() const {
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
    int getSize() const {
        return size;
    }

    /**
     * @brief Shuffle all cards on deck
     *
     */
    void shuffle() const {
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
    std::string printCards(bool print) const {
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
};

/**
 * @brief Hand structure
 */
class Hand {
   private:
    std::string* cards;
    int numCards;
    int size;

   public:
    /**
     * @brief Construct a new Cards object
     *
     * @param size Maximum number of cards on hand or array size (default: 10)
     */
    Hand(int size)
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
    ~Hand() {
        delete[] cards;
    }

    /**
     * @brief Change or add card into hand
     *
     * @param index Position of card on hand (array index)
     * @param value Value of the card
     */
    void setCard(int index, std::string value) {
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
    void setNull(int index) {
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
    std::string getCard(int index) const {
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
    std::string* getHand() const {
        return cards;
    }

    /**
     * @brief Get card value
     *
     * @param index Position of card on hand (array index)
     * @return int
     */
    int getValue(int index) const {
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
    std::array<int, 2> getTotalValue() const {
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
    int getHandSize() const {
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
    int getSize() const {
        return size;
    }

    /**
     * @brief Draws 2 or less cards from deck
     *
     * @param obj Deck class object
     */
    void drawCards(Deck obj) {
        std::string* deck = obj.getDeck();
        int deckSize = obj.getDeckSize();  // PP size

        int firstIndex = -1;
        int secondIndex = -1;
        for (int i = numCards; i < size - numCards; i++) {
            if (numCards + 1 > deckSize) break;

            if (deck[i] != "" && firstIndex == -1) {
                firstIndex = i;
                numCards++;
            } else if (deck[i] != "" && secondIndex == -1) {
                secondIndex = i;
                numCards++;
                break;
            }
        }

        setCard(numCards, deck[firstIndex]);
        setCard(numCards + 1, deck[secondIndex]);
        deck[firstIndex] = "";
        deck[secondIndex] = "";

        int prevIndex = 0;
        for (int i = 0; i < deckSize; i++) {
            if (deck[i] != "") {
                deck[prevIndex] = deck[i];
                prevIndex++;
            }
        }
        for (int i = prevIndex; i < deckSize; i++) {
            deck[i] = "";
        }
    }

    /**
     * @brief Get a formatted string of all cards on hand (optional: print to console)
     *
     * @param print Whether to print to console or not
     * @return std::string All cards on hand (formatted string)
     */
    std::string printCards(bool print) const {
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
};

// PROTOTYPES
void title();
void DisplayCards();
bool exitPromptHandler(bool, bool);

/**
 * @brief Start Blackjack game
 *
 * @return Error status (int)
 */
int blackjack() {
    return 0;
}

// SYSTEM FUNCTIONS

void title() {
    std::cout << "---------------------------- \n";
    std::cout << "    Welcome to Blackjack     \n";
    std::cout << "---------------------------- \n\n";
}

// Use this for restart / exit  check only
bool exitPromptHandler(bool win, bool gameEnded) {
    std::string message;
    if (gameEnded)
        switch (win) {
            case true:
                message = "Do you like to play again? ";
                break;
            case false:
                message = "Would you like to try again? ";
                break;
        }
    else
        message = "Would you like to play? ";

    answer = stringPrompt(message, true);

    const std::string arrTrue[] = {"yes", "y", "naur", "yeah", "yep"};  // Responses for true
    const std::string arrFalse[] = {"no", "n", "naur", "nah", "nope"};  // Responses for false
    const int numArrTrue = sizeof(arrTrue) / sizeof(arrTrue[0]);        // Number of elements in array
    const int numArrFalse = sizeof(arrFalse) / sizeof(arrFalse[0]);     // Number of elements in array

    if (numArrTrue == numArrFalse) {
        for (int i = 0; i < numArrTrue; i++)  // Computing shortcut
            if (answer == arrTrue[i])
                return true;
            else if (answer == arrFalse[i])
                return false;
    } else {
        for (int i = 0; i < numArrTrue; i++)  // Long version
            if (answer == arrTrue[i])
                return true;

        for (int i = 0; i < numArrFalse; i++)
            if (answer == arrFalse[i])
                return false;
    }

    message = "I didn't catch that. " + message;
    return exitPromptHandler(win, gameEnded);
}

// GAME FUNCTIONS

void DisplayCards(Hand dealer, Hand player, bool isStand) {
    std::cout << "Dealer's cards:\n\n";
    if (isStand) {
        dealer.printCards(true);
        std::cout << "Dealer's card count: ";
        std::cout << player.getTotalValue()[0] << (player.getTotalValue()[1] > 0 ? " or " + std::to_string(player.getTotalValue()[1]) : "") << "\n\n";
    } else {
        dealer.getCard(0);
        std::cout << "| " << dealer.getCard(0) << " | ? |" << std::endl;
    }
    std::cout << "\n\n";

    std::cout << "Your cards:\n\n";
    player.printCards(true);
    std::cout << "\n\n";

    std::cout << "Your card count: ";
    std::cout << player.getTotalValue()[0] << (player.getTotalValue()[1] > 0 ? " or " + std::to_string(player.getTotalValue()[1]) : "") << "\n\n";
}