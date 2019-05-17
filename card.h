#ifndef CARD_H
#define CARD_H
#include <iostream>

class Card {
public:
  enum Rank {
    ACE = 1,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING
  };
  enum Suit { SPADES, HEARTS, DIAMONDS, CLUBS };

  Card(Rank rank = ACE, Suit suit = CLUBS, bool isFaceUp = true);

  int getValue() const;

  void flip();

  std::string convert();

private:
  Rank m_rank;
  Suit m_suit;
  bool m_isFaceUp;

public:
  friend std::ostream &operator<<(std::ostream &out, const Card &card);
};

#endif // CARD_H
