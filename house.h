#ifndef HOUSE_H
#define HOUSE_H
#include "abstractplayer.h"

class House : public AbstractPlayer {
public:
  House(const QString &name = "House");

  virtual ~House();

  virtual void makePixmaps(AbstractPlayer &);

  // if total score is <=16, will hit
  virtual bool isHitting() const;

  void flipFirstCard(bool b);

  std::vector<QPixmap> &getPixmaps();

private:
  std::vector<QPixmap> m_pixmaps;
};

#endif // HOUSE_H
