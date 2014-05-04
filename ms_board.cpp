#include "ms_board.h"

#include <iostream>
using namespace std;

MSBoard::MSBoard (QWidget* parent) : QWidget (parent)
{
  height = 10;
  width = 10;

  buttons = new MSButtonVec (height*width);
  msArray = new MSArray (height*width);
  grid = new QGridLayout (this);
  /*
  for (int i=0; i < height*width; ++i){
    MSButton* msb = new MSButton (this);
    connect (msb, SIGNAL(clicked()), this, SLOT(buttonLeftClicked()));
    connect (msb, SIGNAL(rightClicked()), this, SLOT(buttonRightClicked()));
    grid->addWidget (msb, i/height, i%width);
    buttons->insert (i, msb);
    (*msArray)[i] = MSButton::Blank;
  }
  */
  /*
  MSButton* msb = new MSButton (parent);
  grid->addWidget (msb, 0, 0);
  */
  /*
  for (int i=0; i < height*width; ++i){
    QPushButton* b = new QPushButton (this);
    grid->addWidget (b, i/height, i%width);
    connect (b, SIGNAL(clicked()), SLOT(buttonLeftClicked()));
  }
  */
}

MSBoard::~MSBoard ()
{
  /*
  delete buttons;
  delete msArray;
  delete grid;
  */
}

void MSBoard::buttonLeftClicked ()
{
  cout << "clicked" << endl;
}

void MSBoard::buttonRightClicked ()
{

}
