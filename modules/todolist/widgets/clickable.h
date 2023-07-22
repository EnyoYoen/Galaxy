#ifndef CLICKABLE
#define CLICKABLE

#include <QWidget>
#include <QMouseEvent>

class Clickable : public QWidget
{

public:
    Clickable(std::function<void(QMouseEvent *)> handler, QWidget *p);
};

#endif