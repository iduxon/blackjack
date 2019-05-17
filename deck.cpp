#include "deck.h"

Deck::Deck() {
  m_cards.reserve(52);
  populate();
}

Deck::~Deck(){};

void Deck::populate() {
  clear();
  for (int s = Card::SPADES; s <= Card::CLUBS; ++s)
    for (int r = Card::ACE; r <= Card::KING; ++r) {
      add(new Card(static_cast<Card::Rank>(r), static_cast<Card::Suit>(s)));
    }
}

void Deck::shuffle() { random_shuffle(m_cards.begin(), m_cards.end()); }

void Deck::deal(Hand &hand) {
  if (!m_cards.empty()) {
    hand.add(m_cards.back());
    m_cards.pop_back();
  } else {
    std::cout << "Out of cards. Unable to deal." << std::endl;
  }
}

QString Deck::additionalCards(AbstractPlayer &absPlayer) {
  // continues to deal cards untill player has lost or wants more cards
  if (absPlayer.isHitting() && !absPlayer.isBusted())
    deal(absPlayer);
  return absPlayer.makeLabelString();
}
