#ifndef ICONBUTTON
#define ICONBUTTON

#include <QPushButton>

class IconButton : public QPushButton
{

public:
    IconButton(std::function<void()> onClic, QString name, QWidget *p, int size = 30);

private:
    int size;

    virtual void enterEvent(QEnterEvent *);
    virtual void leaveEvent(QEvent *);
};

#endif