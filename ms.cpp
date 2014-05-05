//MS implements the actual game
//MS contains a board, timer, and other features

#include <QFrame>
#include <QMessageBox>

#include <string>
#include <sstream>

#include "ms.h"

using namespace std;

MS::MS (QWidget* parent) : QWidget (parent)
{
  remainingMines = 10;

  //Allocate memory for widgets
  board = new MSBoard (this);
  mainlayout = new QVBoxLayout (this);
  hlayout = new QHBoxLayout;
  timer = new QLabel ("Time Taken");
  newgame = new QPushButton ("New Game");
  string s;
  stringstream ss;
  ss << remainingMines;
  ss >> s;
  numMines = new QLabel (QString::fromStdString(s));

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
  connect (newgame,     SIGNAL(clicked()), 
	   this,        SLOT(newGameClicked()));
  connect (board,       SIGNAL(finished(MSBoard::State)),
	   this,        SLOT(gameOver(MSBoard::State)));
  connect (board,       SIGNAL(flagsChanged(int)), 
	   this,        SLOT(changeRemainingMines(int)));
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
  remainingMines = 10;
  numMines->setText ("10");
}

void MS::gameOver (MSBoard::State s)
{
  if (s == MSBoard::Win)
    QMessageBox::information (this, "Game Over", "You Win!");
  else
    QMessageBox::information (this, "Game Over", "You Lose!");
}

void MS::changeRemainingMines (int change)
{
  remainingMines += change;
  string s;
  stringstream ss;
  ss << remainingMines;
  ss >> s;
  numMines->setText (QString::fromStdString(s));
}
