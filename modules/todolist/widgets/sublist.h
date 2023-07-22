#ifndef SUBLIST
#define SUBLIST

#include "../tools/json.h"
#include "element.h"
#include "iconbutton.h"

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

class Sublist : public QLabel
{
    Q_OBJECT
public:
    Sublist(Id list, Id sublist, QWidget *p);

    void rename(QString name);
    bool dropElement(Element *element, int y);

    QVBoxLayout *lay = nullptr; 

signals:
    void renameButtonClicked();
    void deleteButtonClicked();
    void popupRequest(QStringList prompts, QString title, std::function<void(bool, QStringList)> handler);
    void pressed(QPointF offset);
    void elementPressed(QPointF offset, QPointF pos, Id elementId, int layPos, Element *element);

private:
    QLabel *title = nullptr;
    QPushButton *addButton = nullptr;
    IconButton *renameButton = nullptr;
    IconButton *deleteButton = nullptr;
    QList<Element *> elements;
    Id list, sublist;
    bool press = false;

    void createElement(QString name, QString content, Id elementId);

    virtual void mousePressEvent(QMouseEvent *e);
};

#endif