#ifndef MS_H
#define MS_H

//MS implements the actual game
//MS contains a board, timer, and other features

#include <QWidget>

class MS : public QWidget
{
  Q_OBJECT

  public:
    MS(QWidget* parent = 0);
    ~MS();

  private:
};

#endif
