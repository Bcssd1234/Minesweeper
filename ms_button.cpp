#include <QPainter>
#include <string>
#include <sstream>

#include "ms_button.h"

using namespace std;

MSButton::MSButton (QWidget* parent) : QPushButton (parent)
{
  t = Blank;
  isMine = false;
  adjacentMines = 0;
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
    if (isMine == true)
      p.drawText (r, Qt::AlignCenter, "M");
    else if (adjacentMines != 0){
      stringstream ss;
      string num;
      ss << adjacentMines;
      ss >> num;
      p.drawText (r, Qt::AlignCenter, QString::fromStdString(num));
    }
  }

  else if (t == Flag){
    //later change to actual flag
    p.drawText (r, Qt::AlignCenter, "F");
  }

  else if (t == Question){
    p.drawText (r, Qt::AlignCenter, "?");
  }

  else if (t == X){
    p.setPen (Qt::SolidLine);
    //p.setBrush (Qt::red);
    p.drawLine (r.topLeft() + QPoint(4,4), r.bottomRight() - QPoint(4,4));
    p.drawLine (r.bottomLeft() + QPoint(4,-4), r.topRight() - QPoint(4,-4));
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
