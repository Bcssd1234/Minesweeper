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

  if (t == Pushed){
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

void MSButton::mousePressEvent (QMouseEvent* event)
{
  setDown (true);

  if (event->button() == Qt::RightButton)
    emit rightClicked();
  else
    emit leftClicked();
}

void MSButton::mouseReleaseEvent (QMouseEvent* event)
{
  //For some reason, right-clicked buttons stay down until another button is
  //clicked, so I have to set each button back up here
  if (type() != Pushed)
    setDown (false);
}
