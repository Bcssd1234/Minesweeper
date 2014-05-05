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
  time = new QLabel ("0");
  newgame = new QPushButton ("New Game");
  timer = new QTimer (this);
  string s;
  stringstream ss;
  ss << remainingMines;
  ss >> s;
  numMines = new QLabel (QString::fromStdString(s));

  //Initialization
  numMines->setFrameStyle (QFrame::WinPanel | QFrame::Sunken);
  numMines->setAlignment (Qt::AlignCenter);
  time->setFrameStyle (QFrame::WinPanel | QFrame::Sunken);
  time->setAlignment (Qt::AlignCenter);
  curTime = 0;
  timer->setInterval (1000);

  //Create layout
  mainlayout->addLayout (hlayout);
  mainlayout->addWidget (board);

  hlayout->addWidget (numMines);
  hlayout->addWidget (newgame);
  hlayout->addWidget (time);

  //Connect signals and slots
  connect (newgame,     SIGNAL(clicked()), 
	   this,        SLOT(newGameClicked()));
  connect (board,       SIGNAL(finished(MSBoard::State)),
	   this,        SLOT(gameOver(MSBoard::State)));
  connect (board,       SIGNAL(flagsChanged(int)), 
	   this,        SLOT(changeRemainingMines(int)));
  connect (board,       SIGNAL(beginTimer()),
	   this,        SLOT(startTimer()));
  connect (timer,       SIGNAL(timeout()),
	   this,        SLOT(updateTime()));
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
  curTime = 0;
  time->setText ("0");
}

void MS::gameOver (MSBoard::State s)
{
  timer->stop();
  board->timerIsActive = false;

  if (s == MSBoard::Win){
    QMessageBox information (this);
    information.setWindowTitle ("Game Over");
    information.setText ("You Win!");
    information.setIcon (QMessageBox::Information);
    string s;
    stringstream ss;
    ss << "Time: ";
    ss << curTime;
    s = ss.str();
    information.setInformativeText (QString::fromStdString(s));
    information.exec ();
  }
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

void MS::startTimer ()
{
  timer->start();
}

void MS::updateTime ()
{
  ++curTime;
  string s;
  stringstream ss;
  ss << curTime;
  ss >> s;
  time->setText (QString::fromStdString(s));
}
