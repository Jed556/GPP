#ifndef BLACKJACK_H
#define BLACKJACK_H

#include <array>
#include <string>

class Deck {
   private:
    std::string* suits;
    std::string* faces;
    size_t numSuits;
    size_t numFaces;
    std::string* cards;
    size_t size;

   public:
    Deck(std::string* suits, int numSuits, std::string* faces, int numFaces);
    ~Deck();
    void setCard(int index, std::string value);
    void setNull(int index);
    std::string getCard(int index) const;
    std::string* getDeck() const;
    int getDeckSize() const;
    size_t getSize() const;
    void shuffle() const;
    std::string printCards(bool print) const;
};

class Hand {
   private:
    std::string* cards;
    int numCards = 0;
    size_t size = 0;

   public:
    Hand(size_t size);
    ~Hand();
    void setCard(int index, std::string value);
    void setNull(int index);
    std::string getCard(int index) const;
    std::string* getHand() const;
    int getValue(int index) const;
    std::array<int, 2> getTotalValue() const;
    int getHandSize() const;
    size_t getSize() const;
    void drawCards(Deck& obj, int numDraws);
    std::string printCards(bool print) const;
};

#endif  // BLACKJACK_H