#ifndef ICONBUTTON
#define ICONBUTTON

#include <QPushButton>

class IconButton : public QPushButton
{

public:
    IconButton(std::function<void()> onClic, QString name, QWidget *p, size_t size = 30);

private:
    size_t size;

    virtual void enterEvent(QEnterEvent *);
    virtual void leaveEvent(QEvent *);
};

#endif