#include "game.h"

Game::Game(const std::vector<QString> &names, Canvas *canvas)
    : m_canvas(canvas) {
  std::vector<QString>::const_iterator pName;
  for (pName = names.begin(); pName != names.end(); ++pName)
    m_player.push_back(Player(*pName));
  srand(time(nullptr));
  m_deck.populate();
  m_deck.shuffle();
}

Game::~Game() {}

void Game::gameStarted() {
  QString qstr = " ";

  // deletes the cards for everybody
  std::vector<Player>::iterator iterPlayer;
  for (iterPlayer = m_player.begin(); iterPlayer != m_player.end();
       ++iterPlayer)
    iterPlayer->clear();
  m_house.clear();

  Player::resetHitCount();

  m_canvas->clearIcons();
  m_canvas->setResultLabel(qstr);

  setStand(true);

  // deal first 2 cards to everybody
  for (int i = 0; i < 2; ++i) {
    for (iterPlayer = m_player.begin(); iterPlayer != m_player.end();
         ++iterPlayer)
      m_deck.deal(*iterPlayer);
    m_deck.deal(m_house);
  }

  // hide host's first card
  if (!Player::getHitCount())
    m_house.flipFirstCard(true);

  // show all hands
  for (iterPlayer = m_player.begin(); iterPlayer != m_player.end();
       ++iterPlayer) {
    qstr = iterPlayer->makeLabelString();
    m_canvas->setPlayerStateLabel(qstr);
    iterPlayer->makePixmaps(*iterPlayer);
    m_canvas->drawCards(*iterPlayer);
  }
  qstr = m_house.makeLabelString();
  m_canvas->setHostStateLabel(qstr);
  m_house.makePixmaps(m_house);
  m_canvas->drawCards(m_house);
}

void Game::hitSelected() {
  QString qstr;
  std::vector<Player>::iterator iterPlayer;
  if (!Player::getHitCount())
    m_house.flipFirstCard(true);

  // deal cards to players
  for (iterPlayer = m_player.begin(); iterPlayer != m_player.end();
       ++iterPlayer) {
    iterPlayer->setHitCount();
    qstr = m_deck.additionalCards(*iterPlayer);
    m_canvas->setPlayerStateLabel(qstr);
    iterPlayer->makePixmaps(*iterPlayer);
    m_canvas->drawCards(*iterPlayer);
  }

  // deal cards to host
  qstr = m_deck.additionalCards(m_house);
  m_house.makeLabelString();
  m_canvas->setHostStateLabel(qstr);
  m_house.makePixmaps(m_house);
  m_canvas->drawCards(m_house);

  if (m_house.isBusted()) {
    qstr = m_house.bust();
    m_canvas->setResultLabel(qstr);
    for (iterPlayer = m_player.begin(); iterPlayer != m_player.end();
         ++iterPlayer) {
      if (!iterPlayer->isBusted())
        iterPlayer->win(*m_canvas);
      else
        // both lost
        iterPlayer->lose(*m_canvas);
    }
  } else {
    for (iterPlayer = m_player.begin(); iterPlayer != m_player.end();
         ++iterPlayer) {
      // player is still playing,hasnt lost
      if (!(iterPlayer->isBusted())) {
        if (iterPlayer->isHitting())
          break;
        else {
          while (m_house.isHitting()) {
            qstr = m_deck.additionalCards(m_house);
            m_house.makeLabelString();
            m_house.makePixmaps(m_house);
            m_canvas->drawCards(m_house);
          }
        }
        if (iterPlayer->getTotal() > m_house.getTotal())
          iterPlayer->win(*m_canvas);
        else if (iterPlayer->getTotal() < m_house.getTotal())
          iterPlayer->lose(*m_canvas);
        else
          iterPlayer->push(*m_canvas);
      }
      // player lost
      else {
        iterPlayer->lose(*m_canvas);
        qstr = iterPlayer->bust();
        m_canvas->setResultLabel(qstr);
      }
    }
  }
}

// the player is asked weather or not he wants to end , host will ask for hit
// if he has <=16
void Game::standSelected() {
  std::vector<Player>::iterator iterPlayer;
  QString qstr;

  if (Player::getHitCount()) {
    m_house.flipFirstCard(false);
    Player::setHitCount();
  } else {
    m_house.flipFirstCard(true);
    Player::setHitCount();
  }

  // deal additional cards to host
  qstr = m_deck.additionalCards(m_house);
  m_house.makeLabelString();
  m_canvas->setHostStateLabel(qstr);
  m_house.makePixmaps(m_house);
  m_canvas->drawCards(m_house);

  if (m_house.isBusted()) {
    qstr = m_house.bust();
    m_canvas->setResultLabel(qstr);
    for (iterPlayer = m_player.begin(); iterPlayer != m_player.end();
         ++iterPlayer)
      if (!iterPlayer->isBusted())
        iterPlayer->win(*m_canvas);
  } else {
    for (iterPlayer = m_player.begin(); iterPlayer != m_player.end();
         ++iterPlayer) {
      if (!m_house.isHitting()) {
        if (iterPlayer->getTotal() > m_house.getTotal())
          iterPlayer->win(*m_canvas);
        else if (iterPlayer->getTotal() < m_house.getTotal())
          iterPlayer->lose(*m_canvas);
        else {
          iterPlayer->push(*m_canvas);
        }
      }
    }
  }
}

void Game::setStand(bool b) { m_stand = b; }

bool Game::getStand() { return m_stand; }
