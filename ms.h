#ifndef MS_H
#define MS_H

//MS implements the actual game
//MS contains a board, timer, and other features

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "ms_board.h"

class MS : public QWidget
{
  Q_OBJECT

  public:
    MS(QWidget* parent = 0);
    ~MS();

  private:
    MSBoard* board;
    QVBoxLayout* mainlayout;
    QHBoxLayout* hlayout;
};

#endif
