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

}
