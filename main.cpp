#include "main.h"
#include <QApplication>
#include <QtWidgets>

void startGame();

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  Canvas canvas;
  canvas.show();

  return app.exec();
}
