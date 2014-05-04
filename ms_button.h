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

    bool isMine;
    int adjacentMines;
    
    //Override functions related to the size of the button
    QSizePolicy sizePolicy() const
    { return QSizePolicy( QSizePolicy::Preferred, QSizePolicy::Preferred ); }
    QSize sizeHint() const { return QSize( 32, 32 ); }
    QSize minimumSizeHint() const { return QSize( 10, 10 ); }

    //Minesweeper specific stuff
    enum Type { Blank, Pushed, Flag, Question };
    Type type () const {return t;}
    
    //repaint() triggers a paintEvent
    void setType (Type type) {t = type; repaint();}
    
  //Since QPushButton has no signal for rightClicked,
  //this uses a mousePressEvent to decipher if the button
  //has been left clicked or right clicked
  signals:
    void leftClicked();
    void rightClicked();
    
  private slots:
    void mousePressEvent (QMouseEvent* event);
    
  private:
    Type t;

    void paintEvent (QPaintEvent* event);
    void mouseReleaseEvent (QMouseEvent* event);
};
    
#endif
