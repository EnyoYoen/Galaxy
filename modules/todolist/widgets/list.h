#ifndef LIST
#define LIST

#include "../tools/json.h"
#include "sublist.h"
#include "popup.h"
#include "iconbutton.h"

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>

class List : public QWidget
{
    Q_OBJECT
public:
    List(Id id, QWidget *p);

    void newElement();

signals:
    void back();
    void deleted();
    void renamed();

public slots:
    void addSublist();

private:
    QVBoxLayout *lay = nullptr;
    QWidget *header = nullptr;
    QHBoxLayout *headerLay = nullptr; 
    QPushButton *backButton = nullptr;
    QLabel *title = nullptr;
    IconButton *editNameButton = nullptr;
    IconButton *deleteButton = nullptr;
    QWidget *sublistsContainer = nullptr;
    QHBoxLayout *sublistsContainerLay = nullptr;
    QPushButton *newSublistButton = nullptr;
    PopUp *popup = nullptr;
    QList<Sublist *> sublists;
    Id id;

    Sublist *sublist = nullptr;
    QPointF sublistDragOffset;
    Id sublistPressedId = InvalidId;
    bool sublistPressed = false;

    Element *element = nullptr;
    Sublist *elementSublist = nullptr;
    QPointF elementDragOffset;
    Id elementPressedId = InvalidId;
    int elementLayPos;
    bool elementPressed = false;

    void createSublist(QString title, Id sublistId);

    virtual void mousePressEvent(QMouseEvent *e);
    virtual void mouseReleaseEvent(QMouseEvent *e);
    virtual void mouseMoveEvent(QMouseEvent *e);
};

#endif