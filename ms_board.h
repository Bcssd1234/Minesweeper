#ifndef MS_BOARD_H
#define MS_BOARD_H

#include <QWidget>
#include <QGridLayout>

#include "ms_button.h"

//These are template vectors that will be used to store
//the buttons and the current state of the buttons.
typedef QVector<MSButton*> MSButtonVec
typedef QVector<int> MSArray;

class MSBoard : public QWidget
{
  Q_OBJECT

  public:
    MSBoard (QWidget* parent);
    ~MSBoard ();
    void newGame ();

  private slots:
    buttonLeftClicked ();
    buttonRightClicked ();

  private:
    void updateButtons ();

    MSButtonVec* buttons;  //Stores the actual buttons
    MSArray* msArray;      //Stores the current state of the buttons
    QGridLayout* grid;
};

#endif
