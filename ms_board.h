#ifndef MS_BOARD_H
#define MS_BOARD_H

#include <QWidget>

#include "ms_button.h"

class MSBoard : public QWidget
{
  Q_OBJECT

  public:
    MSBoard (QWidget* parent);
    ~MSBoard ();

  private:
};

#endif
