#include "hand.h"

Hand::Hand() { m_cards.reserve(5); }
Hand::~Hand() { clear(); }

void Hand::add(Card *pCard) { m_cards.push_back(pCard); }

void Hand::clear() {
  std::vector<Card *>::iterator iter = m_cards.begin();

  for (; iter != m_cards.end(); ++iter) {
    delete *iter;
    *iter = nullptr;
  }

  m_cards.clear();
}

int Hand::getTotal() const {
  if (m_cards.empty())
    return 0;

  // if the first card = 0 ,it means all cards are facing down
  // faster to check a value inside our class,then call
  if (m_cards[0]->getValue() == 0)
    return 0;

  int total = 0;
  bool containsAce = false;

  std::vector<Card *>::const_iterator iter;
  for (iter = m_cards.cbegin(); iter != m_cards.cend(); ++iter) {
    total += (*iter)->getValue();
    if ((*iter)->getValue() == Card::ACE)
      containsAce = true;
  }
  if (containsAce && total <= 11)
    total += 10;

  return total;
}
