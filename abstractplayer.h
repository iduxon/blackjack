#ifndef ABSTRACTPLAYER_H
#define ABSTRACTPLAYER_H

#include "hand.h"
#include "main.h"

#include <QApplication>
#include <QPixmap>
#include <QString>
#include <iostream>
#include <vector>

class AbstractPlayer : public Hand {

  friend std::ostream &operator<<(std::ostream &out,
                                  const AbstractPlayer &player);

public:
  AbstractPlayer(const QString &str = "");
  QString makeLabelString();
  virtual void makePixmaps(AbstractPlayer &);

  virtual ~AbstractPlayer();

  // shows if the player wants another hit
  virtual bool isHitting() const = 0;

  // shows if player has lost
  bool isBusted() const;

  QString bust() const;

  QString &getLabelQStr() const;
  QString getName() const;

protected:
  QString m_name;
  Hand *m_hand;
  mutable QString labelQStr;
};

class Player : public AbstractPlayer {
public:
  Player(const QString &name = "");

  virtual ~Player();

  virtual void makePixmaps(AbstractPlayer &);

  // next card or not
  virtual bool isHitting() const;

  void win(Canvas &) const;

  void lose(Canvas &) const;

  // it's a tie
  void push(Canvas &) const;

  static void resetHitCount();
  static void setHitCount();
  static int getHitCount();

  void resultMessage(QString &s) const;
  std::vector<QPixmap> &getPixmaps();

private:
  static int m_hitCount;
  std::vector<QPixmap> m_pixmaps;
};

#endif // ABSTRACTPLAYER_H
