#include "card.h"
#include <sstream>
Card::Card(Rank rank, Suit suit, bool isFaceUp)
    : m_rank(rank), m_suit(suit), m_isFaceUp(isFaceUp) {}

int Card::getValue() const {
  int value = 0;
  if (m_isFaceUp) {
    value = m_rank;
    if (value > 10)
      value = 10;
  }
  return value;
}

void Card::flip() { m_isFaceUp = !m_isFaceUp; }

std::string Card::convert() {
  std::ostringstream oss;
  std::string str;
  const std::string RANKS[] = {"0",  "14", "02", "03", "04", "05", "06",
                               "07", "08", "09", "10", "11", "12", "13"};
  const std::string SUITS[] = {"1", "2", "3", "4"};

  if (m_isFaceUp)
    oss << ":images/" << SUITS[m_suit] << RANKS[m_rank] << ".gif";
  else {
    oss << ":images/"
        << "xx"
        << ".gif";
  }
  str = oss.str();
  return str;
}

std::ostream &operator<<(std::ostream &out, const Card &card) {
  const std::string RANKS[] = {"0", "A", "2", "3",  "4", "5", "6",
                               "7", "8", "9", "10", "J", "Q", "K"};
  const std::string SUITS[] = {"s", "h", "d", "c"};

  if (card.m_isFaceUp)
    out << RANKS[card.m_rank] << SUITS[card.m_suit];
  else {
    out << "XX";
  }
  return out;
}
