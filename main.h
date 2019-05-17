#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <string>
#include <vector>

#include <QApplication>
#include <QCheckBox>
#include <QDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QListView>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

const int MAXCARDS = 10;

class QLabel;
class QLineEdit;
class QTextEdit;
class QPushButton;
class QString;
class Player;
class Game;
class AbstractPlayer;

class Canvas : public QWidget {
  Q_OBJECT
public:
  Canvas(QWidget *parent = nullptr);
  void setHostStateLabel(QString &s);
  void setPlayerStateLabel(QString &s);
  void setResultLabel(QString &s);
  void drawCards(AbstractPlayer &);
  void setupIcons();
  void clearIcons();
  void setEnableHitStandButtons(bool b);

public slots:
  void startBtn();
  void hitBtn();
  void standBtn();

private:
  QPushButton *m_startButton;
  QPushButton *m_hitButton;
  QPushButton *m_standButton;
  QLabel *m_hostState;
  QLabel *m_playerState;
  QLabel *m_result;
  Game *m_myGame;
  QListView *m_cardTable;
  QLabel *m_cardIconHouse[MAXCARDS];
  QLabel *m_cardsIconPlayer[MAXCARDS];
};

#endif // MAIN_H
