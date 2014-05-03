//MS implements the actual game
//MS contains a board, timer, and other features

#include <QFrame>

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
  timer->setFrameStyle (QFrame::WinPanel | QFrame::Sunken);

  //Create layout
  mainlayout->addLayout (hlayout);
  mainlayout->addWidget (board);

  hlayout->addWidget (numMines);
  hlayout->addWidget (newgame);
  hlayout->addWidget (timer);

  //Connect signals and slots
}

MS::~MS()
{

}
