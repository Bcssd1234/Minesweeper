//MS implements the actual game
//MS contains a board, timer, and other features

#include <QFrame>
#include <QMessageBox>

#include "ms.h"

MS::MS (QWidget* parent) : QWidget (parent)
{
  //Allocate memory for widgets
  board = new MSBoard (this);
  mainlayout = new QVBoxLayout (this);
  hlayout = new QHBoxLayout;
  numMines = new QLabel ("# Mines");
  timer = new QLabel ("Time Taken");
  newgame = new QPushButton ("New Game");

  //Initialization
  numMines->setFrameStyle (QFrame::WinPanel | QFrame::Sunken);
  numMines->setAlignment (Qt::AlignCenter);
  timer->setFrameStyle (QFrame::WinPanel | QFrame::Sunken);
  timer->setAlignment (Qt::AlignCenter);

  //Create layout
  mainlayout->addLayout (hlayout);
  mainlayout->addWidget (board);

  hlayout->addWidget (numMines);
  hlayout->addWidget (newgame);
  hlayout->addWidget (timer);

  //Connect signals and slots
  connect (newgame, SIGNAL(clicked()), this, SLOT(newGameClicked()));
  connect (board, SIGNAL(finished(MSBoard::State)), this, SLOT(gameOver(MSBoard::State)));
}

MS::~MS ()
{
  //delete board;
  //delete mainlayout;
  //delete hlayout;
  //delete numMines;
  //delete timer;
  //delete newgame;
}

void MS::newGameClicked ()
{
  board->newGame ();
}

void MS::gameOver (MSBoard::State s)
{
  if (s == MSBoard::Win)
    QMessageBox::information (this, "Game Over", "You Win!");
  else
    QMessageBox::information (this, "Game Over", "You Lose!");
}
