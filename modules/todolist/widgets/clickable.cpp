#include "clickable.h"

#include "filters.h"

Clickable::Clickable(std::function<void(QMouseEvent *)> handler, QWidget *p)
    : QWidget(p)
{
    ClicFilter *f = new ClicFilter(handler);
    installEventFilter(f);
}