#include "abstractplayer.h"
#include <QMessageBox>
#include <sstream>

AbstractPlayer::AbstractPlayer(const QString &str) : m_name(str) {}

AbstractPlayer::~AbstractPlayer() {}

QString AbstractPlayer::getName() const { return m_name; }

QString &AbstractPlayer::getLabelQStr() const { return labelQStr; }

QString AbstractPlayer::makeLabelString() {
  std::string str = "";
  std::ostringstream oss;
  oss << "";
  oss << m_name.toStdString() << ":   ";

  std::vector<Card *>::const_iterator pCard;
  if (!m_cards.empty()) {
    for (pCard = m_cards.begin(); pCard != m_cards.end(); ++pCard) {
      oss << *(*pCard) << "   ";
    }
    if (getTotal() != 0) {
      oss << "(" << getTotal() << ")";
    }
  } else {
    oss << "<empty>";
  }
  str = oss.str();
  return str.c_str();
}

bool AbstractPlayer::isBusted() const { return (getTotal() > 21); }

void AbstractPlayer::makePixmaps(AbstractPlayer &absPlayer) {}

std::ostream &operator<<(std::ostream &out, const AbstractPlayer &absPlayer) {
  std::string str = "";
  std::ostringstream oss;

  oss << "";
  oss << absPlayer.m_name.toStdString() << ":   ";

  std::vector<Card *>::const_iterator pCard;
  if (!absPlayer.m_cards.empty()) {
    for (pCard = absPlayer.m_cards.begin(); pCard != absPlayer.m_cards.end();
         ++pCard) {
      oss << *(*pCard) << "   ";
    }
    if (absPlayer.getTotal() != 0)
      oss << "(" << absPlayer.getTotal() << ")";
  } else {
    oss << "<empty>";
  }
  str = oss.str();
  absPlayer.labelQStr = str.c_str();
  return out;
}

QString AbstractPlayer::bust() const {
  std::string str = "";
  std::ostringstream oss;
  oss << "";
  oss << m_name.toStdString() << " bust";
  str = oss.str();
  return str.c_str();
}

int Player::m_hitCount = 0;

Player::Player(const QString &name) : AbstractPlayer(name) {}

Player::~Player() {}

int Player::getHitCount() { return m_hitCount; }

void Player::resetHitCount() { m_hitCount = 0; }

void Player::setHitCount() { m_hitCount++; }

bool Player::isHitting() const { return getHitCount(); }

void Player::win(Canvas &cnvs) const {
  QString s = "";
  s.append(m_name);
  s.append(" WON!");
  resultMessage(s);
  cnvs.setEnableHitStandButtons(false);
}

void Player::lose(Canvas &cnvs) const {
  QString s = "";
  s.append(m_name);
  s.append(" LOST!");
  resultMessage(s);
  cnvs.setEnableHitStandButtons(false);
}

// tie
void Player::push(Canvas &cnvs) const {
  QString s = "";
  s.append("PUSH!");
  resultMessage(s);
  cnvs.setEnableHitStandButtons(false);
}

void Player::resultMessage(QString &s) const {
  QMessageBox msgBox;
  msgBox.setWindowTitle("Results. . .");
  msgBox.setText(s);
  msgBox.exec();
}

void Player::makePixmaps(AbstractPlayer &absPlayer) {
  std::string str;
  std::vector<Card *>::const_iterator pCard;
  if (!m_cards.empty()) {
    Player *ptr = dynamic_cast<Player *>(&absPlayer);

    ptr->m_pixmaps.clear();
    for (pCard = m_cards.cbegin(); pCard != m_cards.cend(); ++pCard) {
      str = (*pCard)->convert();
      m_pixmaps.push_back(QPixmap(str.c_str()));
    }
  }
}

std::vector<QPixmap> &Player::getPixmaps() { return m_pixmaps; }
