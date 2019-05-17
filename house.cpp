#include "house.h"

House::House(const QString &name) : AbstractPlayer(name) {}

bool House::isHitting() const { return (getTotal() <= 16); }

House::~House(){};

void House::flipFirstCard(bool b) {
  if (!m_cards.empty()) {
    if (b)
      m_cards[0]->flip();
  }
}

void House::makePixmaps(AbstractPlayer &absPlayer) {
  std::string str;
  std::vector<Card *>::const_iterator pCard;
  if (!m_cards.empty()) {
    House *ptr = dynamic_cast<House *>(&absPlayer);

    ptr->m_pixmaps.clear();
    for (pCard = m_cards.cbegin(); pCard != m_cards.cend(); ++pCard) {
      str = (*pCard)->convert();
      m_pixmaps.push_back(QPixmap(str.c_str()));
    }
  }
}

std::vector<QPixmap> &House::getPixmaps() { return m_pixmaps; }
