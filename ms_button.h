#ifndef MS_BUTTON_H
#define MS_BUTTON_H

#include <QPushButton>
#include <QMouseEvent>

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

  //Since QPushButton has no signal for rightClicked,
  //this uses a mousePressEvent to decipher if the button
  //has been right clicked
  signals:
    void rightClicked();

  private slots:
    void mousePressEvent (QMouseEvent* event);



  private:
    bool isMine;
    Type t;

    void paintEvent (QPaintEvent* event);
};

#endif
