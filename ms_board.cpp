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
  
  for (int i=0; i < height*width; ++i){
    MSButton* msb = new MSButton (this);
    connect (msb, SIGNAL(leftClicked()), this, SLOT(buttonLeftClicked()));
    connect (msb, SIGNAL(rightClicked()), this, SLOT(buttonRightClicked()));
    grid->addWidget (msb, i/height, i%width);
    buttons->insert (i, msb);
    (*msArray)[i] = MSButton::Blank;
  }
}

MSBoard::~MSBoard ()
{
  //delete all the buttons?
  delete buttons;
  delete msArray;
  delete grid;
}

void MSBoard::buttonLeftClicked ()
{

}

void MSBoard::buttonRightClicked ()
{

}

void MSBoard::newGame ()
{
  for (int i=0; i < height*width; ++i)
    (*msArray)[i] = MSButton::Blank;

  updateButtons ();
}

void MSBoard::updateButtons ()
{
  for (int i=0; i < height*width; ++i){
    if (buttons->at(i)->type() != msArray->at(i) ){
      buttons->at(i)->setType ((MSButton::Type)msArray->at(i) );
    }
    buttons->at(i)->setEnabled ((MSButton::Type)msArray->at(i) != MSButton::Pushed);
  }
}

bool MSBoard::checkBoard ()
{

}
