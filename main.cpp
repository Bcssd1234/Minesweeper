#include <QApplication>

#include "ms.h"

int main (int argc, char* argv[])
{
  QApplication app (argc, argv);

  MS ms;
  ms.show();

  return app.exec();
}
