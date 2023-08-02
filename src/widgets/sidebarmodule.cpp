#include "sidebarmodule.h"

SidebarModule::SidebarModule(QString name, QWidget *parent)
    : QWidget(parent)
{
    lay = new QHBoxLayout(this);
    title = new QLabel(name, this);

    lay->addWidget(title, 0, Qt::AlignCenter);

    title->setProperty("class", "sidebar-module-title");
    setProperty("class", "sidebar-module");

    setFixedSize(80, 80);
}

void SidebarModule::mousePressEvent(QMouseEvent *e)
{
    emit pressed(e->position(), e->scenePosition());
}