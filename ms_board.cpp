#include <cstdlib>
#include <queue>

#include "ms_board.h"

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
    if ((b->isMine == true) || (b->adjacentMines != 0)){
      int s = 0;
      (*msArray)[i] = MSButton::Pushed;
      updateButtons ();
      s = checkBoard ();
      if (s == 1){
	gameWon ();
	emit finished (Win);
      }
      else if (s == -1){
	gameLost ();
	emit finished (Lose);
      }
    }

    //If the chosen spot is not a mine and has 0 adjacent mines
    //then all surroundnig spots must be pushed until
    //buttons with > 0 adjacent mines are reached on all sides
    else{
      //Only buttons with 0 surrounding mines will be placed on the queue
      queue<int> q;
      q.push (i);
      while (!q.empty()){
	int cur = q.front();
	q.pop();
	(*msArray)[cur] = MSButton::Pushed;

	//Check 3 touching button above the current location
	if (cur/height > 0){
	  //Button directly above must exist
	  if ((*msArray)[cur-width] == MSButton::Blank){
	    if (buttons->at(cur-width)->adjacentMines == 0)
	      q.push (cur-width);
	    else
	      (*msArray)[cur-width] = MSButton::Pushed;
	  }

	  if (cur%width > 0){
	    if ((*msArray)[cur-width-1] == MSButton::Blank){
	      if (buttons->at(cur-width-1)->adjacentMines == 0)
		q.push (cur-width-1);
	      else
		(*msArray)[cur-width-1] = MSButton::Pushed;
	    }
	  }
	  if (cur%width < width-1){
	    if ((*msArray)[cur-width+1] == MSButton::Blank){
	      if (buttons->at(cur-width+1)->adjacentMines == 0)
		q.push (cur-width+1);
	      else
		(*msArray)[cur-width+1] = MSButton::Pushed;
	    }
	  }
	}

	//Check 3 touching button below the current location
	if (cur/height < height-1){
	  //Button directly below must exist
	  if ((*msArray)[cur+width] == MSButton::Blank){
	    if (buttons->at(cur+width)->adjacentMines == 0)
	      q.push (cur+width);
	    else
	      (*msArray)[cur+width] = MSButton::Pushed;
	  }

	  if (cur%width > 0){
	    if ((*msArray)[cur+width-1] == MSButton::Blank){
	      if (buttons->at(cur+width-1)->adjacentMines == 0)
		q.push (cur+width-1);
	      else
		(*msArray)[cur+width-1] = MSButton::Pushed;
	    }
	  }
	  if (cur%width < width-1){
	    if ((*msArray)[cur+width+1] == MSButton::Blank){
	      if (buttons->at(cur+width+1)->adjacentMines == 0)
		q.push (cur+width+1);
	      else
		(*msArray)[cur+width+1] = MSButton::Pushed;
	    }
	  }
	}

	//Check left and right
	if (cur%width > 0){
	  if ((*msArray)[cur-1] == MSButton::Blank){
	    if (buttons->at(cur-1)->adjacentMines == 0)
	      q.push (cur-1);
	    else
	      (*msArray)[cur-1] = MSButton::Pushed;
	  }
	}
	if (cur%width < width-1){
	  if ((*msArray)[cur+1] == MSButton::Blank){
	    if (buttons->at(cur+1)->adjacentMines == 0)
	      q.push (cur+1);
	    else
	      (*msArray)[cur+1] = MSButton::Pushed;
	  }
	}
      }
      updateButtons ();
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
    //Decrement remaining mine count
  }
  else if (b->type() == MSButton::Flag){
    (*msArray)[i] = MSButton::Question;
    updateButtons ();
    //Increment remaining mine count
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
  assignMines ();
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
  //Return 0 if the game should continue playing
  //Return 1 if the game has been won
  //Return -1 if the game has been lost

  //Assume won until either
  // a mine has been pushed (lost) or
  // a spot without a mine has not been pushed yet (continue playing)
  int state = 1;

  for (int i=0; i < height*width; ++i){
    if ((buttons->at(i)->type() == MSButton::Pushed) &&
	(buttons->at(i)->isMine == true)){
      state = -1;
      break;
    }
    else if ((buttons->at(i)->type() != MSButton::Pushed) &&
	     (buttons->at(i)->isMine == false))
      state = 0;
  }
  return state;
}

void MSBoard::assignMines ()
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

  //Assign the adjacentMine count to each button
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

void MSBoard::gameWon ()
{
  //Show flags on unflagged mines
  for (int i=0; i < height*width; ++i){
    //Unenable all buttons
    buttons->at(i)->setEnabled (false);
    if ((buttons->at(i)->type() == MSButton::Blank) || 
	(buttons->at(i)->type() == MSButton::Question))
      (*msArray)[i] = MSButton::Flag;
  }
}

void MSBoard::gameLost ()
{
  //Show all mines that are not flagged
  //Show X on wrongly placed flags
  for (int i=0; i < height*width; ++i){
    //Unenable all buttons
    buttons->at(i)->setEnabled (false);
    if ((buttons->at(i)->isMine == true) &&
	(buttons->at(i)->type() != MSButton::Flag))
      (*msArray)[i] = MSButton::Pushed;

    else if ((buttons->at(i)->isMine == false) &&
	     (buttons->at(i)->type() == MSButton::Flag))
      (*msArray)[i] = MSButton::X;
  }
}
