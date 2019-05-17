#include "game.h"
#include <QApplication>
#include <QtWidgets>
#include <typeinfo>

class Game;

Canvas::Canvas(QWidget *parent) : QWidget(parent) {
  m_startButton = new QPushButton(tr("&Start"));
  m_hitButton = new QPushButton(tr("&Hit"));
  m_standButton = new QPushButton(tr("&Stand"));

  connect(m_startButton, SIGNAL(clicked()), this, SLOT(startBtn()));
  connect(m_hitButton, SIGNAL(clicked()), this, SLOT(hitBtn()));
  connect(m_standButton, SIGNAL(clicked()), this, SLOT(standBtn()));

  QHBoxLayout *buttonLayout = new QHBoxLayout;
  buttonLayout->addWidget(m_startButton);
  buttonLayout->addWidget(m_hitButton);
  buttonLayout->addWidget(m_standButton);

  buttonLayout->addStretch();

  m_cardTable = new QListView;
  QLabel *houseLabel = new QLabel(m_cardTable);
  QLabel *playerLabel = new QLabel(m_cardTable);
  houseLabel->setText("House");
  playerLabel->setText("Player");
  houseLabel->move(10, 20);
  playerLabel->move(10, 150);

  QVBoxLayout *verticalLayout = new QVBoxLayout;
  verticalLayout->addLayout(buttonLayout);
  verticalLayout->addWidget(m_cardTable);
  m_hostState = new QLabel("host");
  m_playerState = new QLabel("player");
  m_result = new QLabel("result");
  verticalLayout->addWidget(m_hostState);
  verticalLayout->addWidget(m_playerState);
  verticalLayout->addWidget(m_result);

  QGridLayout *mainLayout = new QGridLayout;

  mainLayout->addLayout(verticalLayout, 0, 0, 1, 1);
  setLayout(mainLayout);

  setWindowTitle(tr("Blackjack "));
  resize(500, 400);

  setEnableHitStandButtons(false);

  setupIcons();
}

void Canvas::setEnableHitStandButtons(bool b) {
  m_hitButton->setEnabled(b);
  m_standButton->setEnabled(b);
}

void Canvas::setupIcons() {
  QPixmap qpx;
  std::string str;

  for (int i = 0; i < MAXCARDS; i++) {
    m_cardIconHouse[i] = new QLabel(m_cardTable);
    str = ":/images/blank.png";
    qpx = QPixmap(str.c_str());
    m_cardIconHouse[i]->setPixmap(qpx);
    m_cardIconHouse[i]->move(80 + 60 * i, 20);
  }

  for (int i = 0; i < MAXCARDS; i++) {
    m_cardsIconPlayer[i] = new QLabel(m_cardTable);
    qpx = QPixmap(":/images/blank.png");
    m_cardsIconPlayer[i]->setPixmap(qpx);
    m_cardsIconPlayer[i]->move(80 + 60 * i, 150);
  }
}

void Canvas::clearIcons() {
  QPixmap qpx = QPixmap(":/images/blank.png");
  for (int i = 0; i < MAXCARDS; i++) {
    m_cardIconHouse[i]->setPixmap(qpx);
  }
  for (int i = 0; i < MAXCARDS; i++) {
    m_cardsIconPlayer[i]->setPixmap(qpx);
  }
}

void Canvas::startBtn() {
  std::vector<QString> names;
  QString name = "You";
  names.push_back(name);

  m_myGame = new Game(names, this);
  m_myGame->gameStarted();
  setEnableHitStandButtons(true);
}

void Canvas::hitBtn() { m_myGame->hitSelected(); }

void Canvas::standBtn() { m_myGame->standSelected(); }

void Canvas::setHostStateLabel(QString &s) { m_hostState->setText(s); }

void Canvas::setPlayerStateLabel(QString &s) { m_playerState->setText(s); }

void Canvas::setResultLabel(QString &s) { m_result->setText(s); }

void Canvas::drawCards(AbstractPlayer &ap) {
  QPixmap qpx;
  std::string str;

  if (typeid(ap) == typeid(Player)) {
    Player *ptr = dynamic_cast<Player *>(&ap);
    int size = (ptr->getPixmaps()).size();
    for (int i = 0; i < size; i++) {
      qpx = (ptr->getPixmaps())[i];
      m_cardsIconPlayer[i]->setPixmap(qpx);
    }
  } else if (typeid(ap) == typeid(House)) {
    House *ptr = dynamic_cast<House *>(&ap);
    int size = (ptr->getPixmaps()).size();
    for (int i = 0; i < size; i++) {
      qpx = (ptr->getPixmaps())[i];
      m_cardIconHouse[i]->setPixmap(qpx);
    }
  }
}
