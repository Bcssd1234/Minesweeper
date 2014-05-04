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
  //find the button that was clicked
  int i;
  for (i=0; i < buttons->size(); ++i){
    if (buttons->at(i) == (MSButton*)sender())
      break;
  }
  MSButton* b = buttons->at(i);

  if (b->type() == MSButton::Blank){
    int s = 0;
    (*msArray)[i] = MSButton::Pushed;
    updateButtons ();
    //s = checkBoard ();
    if (s == 1){
      emit finished (Win);
    }
    else if (s == -1){
      //Display all mines?
      emit finished (Lose);
    }
  }
}

void MSBoard::buttonRightClicked ()
{
  //find the button that was clicked
  int i;
  for (i=0; i < buttons->size(); ++i){
    if (buttons->at(i) == (MSButton*)sender())
      break;
  }
  MSButton* b = buttons->at(i);

  if (b->type() == MSButton::Blank){
    (*msArray)[i] = MSButton::Flag;
    updateButtons ();
  }
  else if (b->type() == MSButton::Flag){
    (*msArray)[i] = MSButton::Question;
    updateButtons ();
  }

  else if (b->type() == MSButton::Question){
    (*msArray)[i] = MSButton::Blank;
    updateButtons ();
  }
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

int MSBoard::checkBoard ()
{
  //Return 0 if the game should continue
  //Return 1 if the game has been won
  //Return -1 if the game has been lost
}
