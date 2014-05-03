#ifndef MS_BUTTON_H
#define MS_BUTTON_H

#include <QPushButton>

class MSButton : public QPushButton
{
  Q_OBJECT

  public:
    MSButton (QWidget* parent);
    ~MSButton ();

    //Minesweeper specific stuff
    enum Type { Blank, Pushed, Flag, Question };
    Type type () const {return t;}

    void setType (Type type) {t = type; repaint();}

  private:
    bool isMine;
    Type t;

    void paintEvent (QPaintEvent* event);
}
