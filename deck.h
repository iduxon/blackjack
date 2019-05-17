#ifndef DECK_H
#define DECK_H
#include "abstractplayer.h"

class Deck : public Hand {
public:
  Deck();

  virtual ~Deck();

  void populate();

  void shuffle();

  // deal a card to the hand
  void deal(Hand &hand);

  QString additionalCards(AbstractPlayer &absPlayer);

private:
  std::vector<QPixmap> pixmaps;
};

#endif // DECK_H
