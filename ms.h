#ifndef MS_H
#define MS_H

//MS implements the actual game
//MS contains a board, timer, and other features

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QTimer>

#include "ms_board.h"

class MS : public QWidget
{
  Q_OBJECT

  public:
    MS(QWidget* parent = 0);
    ~MS();

  private slots:
    void newGameClicked ();
    void gameOver (MSBoard::State s);
    void changeRemainingMines (int change);
    void startTimer ();
    void updateTime ();

  private:
    MSBoard* board;
    QVBoxLayout* mainlayout;
    QHBoxLayout* hlayout;
    QLabel* numMines;
    QLabel* time;
    QPushButton* newgame;
    QTimer* timer;

    int remainingMines;
    int curTime;
};

#endif
