#ifndef GAME_H
#define GAME_H

#include "abstractplayer.h"
#include "deck.h"
#include "house.h"
#include "main.h"
#include <QString>
#include <vector>

class Game {
public:
  Game(const std::vector<QString> &names, Canvas *cnv);

  ~Game();

  void gameStarted();
  void hitSelected();
  void standSelected();
  bool getStand();
  void setStand(bool b);

private:
  Deck m_deck;
  House m_house;
  std::vector<Player> m_player;
  Canvas *m_canvas;
  bool m_stand;
};

#endif // GAME_H
