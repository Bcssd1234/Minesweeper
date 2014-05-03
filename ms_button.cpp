#include <QPainter>

#include "ms_button.h"

MSButton::MSButton (QWidget* parent) : QPushButton (parent)
{
  t = Blank;
  isMine = false;
}

MSButton::~MSButton ()
{

}

void MSButton::paintEvent (QPaintEvent* event)
{
  QPushButton::paintEvent (event);

  QPainter p (this);

  QRect r = rect();

  if (t == Blank){
    p.eraseRect (r);
  }

  else if (t == Pushed){
    //later change to the # of adjacent Mines
    p.drawText (r, Qt::AlignCenter, "P");
  }

  else if (t == Flag){
    //later change to flag
    p.drawText (r, Qt::AlignCenter, "F");
  }

  else if (t == Question){
    p.drawText (r, Qt::AlignCenter, "?");
  }
}
