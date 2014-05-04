#include <cstdlib>

#include "ms_board.h"

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

  srand(time(0));
  newGame();
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
  for (int i=0; i < height*width; ++i){
    (*msArray)[i] = MSButton::Blank;
    buttons->at(i)->isMine = false;
    buttons->at(i)->adjacentMines = 0;
  }

  updateButtons ();
  assignBombs ();
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

void MSBoard::assignBombs ()
{
  //Assign 10 bombs by randomly choosing positions until 10 positions
  //without a bomb are found.  Increment i each time.
  int i = 0;
  while (i < 10){
    int r = rand() % (height*width);
    if (buttons->at(r)->isMine == false){
      buttons->at(r)->isMine = true;
      ++i;
    }
  }

  //Assign the adjacent bomb count to each button
  for (i = 0; i < height*width; ++i){
    if (buttons->at(i)->isMine == true){
      //Check 3 touching buttons above current button
      if (i/height > 0){
	//Button directly above must exist
	buttons->at(i-width)->adjacentMines += 1;

	if (i%width > 0)
	  buttons->at(i-width-1)->adjacentMines += 1;
	if (i%width < width-1)
	  buttons->at(i-width+1)->adjacentMines += 1;
      }

      //Check 3 touching buttons below current button
      if (i/height < height-1){
	//Button directly below must exist
	buttons->at(i+width)->adjacentMines += 1;

	if (i%width > 0)
	  buttons->at(i+width-1)->adjacentMines += 1;
	if (i%width < width-1)
	  buttons->at(i+width+1)->adjacentMines += 1;
      }

      //Check left and right
      if (i%width > 0)
	buttons->at(i-1)->adjacentMines += 1;
      if (i%width < width-1)
	buttons->at(i+1)->adjacentMines += 1;
    }
  }
}
