#ifndef BLACKJACK_H
#define BLACKJACK_H

#include <string>
#include <array>

class Deck {
   private:
    std::string suits[4];
    std::string faces[13];
    std::string* cards;
    int size = 0;

   public:
    Deck();
    ~Deck();
    void setCard(int index, std::string value);
    void setNull(int index);
    std::string getCard(int index) const;
    std::string* getDeck() const;
    int getDeckSize() const;
    int getSize() const;
    void shuffle() const;
    std::string printCards(bool print) const;
};

class Hand {
   private:
    std::string* cards;
    int numCards;
    int size;

   public:
    Hand(int size);
    ~Hand();
    void setCard(int index, std::string value);
    void setNull(int index);
    std::string getCard(int index) const;
    std::string* getHand() const;
    int getValue(int index) const;
    std::array<int, 2> getTotalValue() const;
    int getHandSize() const;
    int getSize() const;
    void drawCards(Deck obj);
    std::string printCards(bool print) const;
};

#endif  // BLACKJACK_H