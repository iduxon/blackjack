#ifndef HAND_H
#define HAND_H

#include "card.h"
#include <vector>

class Hand {
public:
  Hand();
  virtual ~Hand();

  void add(Card *pCard);

  void clear();

  int getTotal() const;

protected:
  std::vector<Card *> m_cards;
};

#endif // HAND_H
