#ifndef ELEMENT
#define ELEMENT

#include "iconbutton.h"
#include "../tools/json.h"

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

class Element : public QWidget
{
    Q_OBJECT
public:
    Element(Id list, Id sublist, Id element, QWidget *p);

    void setNameAndContent(QString nameStr, QString contentStr);

signals:
    void changeButtonClicked();
    void deleteButtonClicked();
    void pressed(QPointF offset, QPointF pos);
    void released(QPointF pos);
    void moved(QPointF pos);

private:
    QVBoxLayout *lay = nullptr; 
    QWidget *header = nullptr;
    QHBoxLayout *headerLay = nullptr;
    QLabel *name = nullptr;
    IconButton *changeButton = nullptr;
    IconButton *deleteButton = nullptr;
    QLabel *content = nullptr;
    Id list, sublist, element;
    bool press = false;

    virtual void enterEvent(QEnterEvent *);
    virtual void leaveEvent(QEvent *);
    virtual void mousePressEvent(QMouseEvent *e);
};

#endif