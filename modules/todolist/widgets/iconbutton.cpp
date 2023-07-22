#include "iconbutton.h"
#include "../tools/logger.h"

#include <QVariant>

IconButton::IconButton(std::function<void()> onClic, QString name, QWidget *p, int m_size)
    : QPushButton(p), size(m_size)
{
    setObjectName(name);
    setFixedSize(size, size);
    setProperty("class", "icon-button");
    setStyleSheet(
        "background-color: #383838;"
        "border: none;"
        "border-radius: " + QString::number(size/2) + "px;"
        "padding: 5px;"
    );

    QObject::connect(this, &QPushButton::clicked, onClic);
}

void IconButton::enterEvent(QEnterEvent *)
{
    // TODO : find a way to update css of this widget from a css file
    //setProperty("class", "icon-button-hover");
    setStyleSheet(
        "background-color: #2196f3;"
        "border: none;"
        "border-radius: " + QString::number(size/2) + "px;"
        "padding: 5px;"
    );
}

void IconButton::leaveEvent(QEvent *)
{
    // TODO : find a way to update css of this widget from a css file
    //setProperty("class", "icon-button-hover");
    setStyleSheet(
        "background-color: #383838;"
        "border: none;"
        "border-radius: " + QString::number(size/2) + "px;"
        "padding: 5px;"
    );
}