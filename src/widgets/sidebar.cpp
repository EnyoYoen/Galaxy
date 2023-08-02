#include "sidebar.h"

Sidebar::Sidebar(QStringList names, QWidget *parent/*, Direction dir*/)
    : QWidget(parent)
{
    lay = new QVBoxLayout(this);
    scroll = new QScrollArea(this);
    scrollContent = new QWidget(scroll);
    scrollLay = new QVBoxLayout(scrollContent);
    title = new QLabel("Modules");

    scroll->setWidget(scrollContent);
    scroll->setContentsMargins(0, 0, 0, 0);
    scroll->setWidgetResizable(true);
    scroll->setAttribute(Qt::WA_StyledBackground, true);
    scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    
    setFixedWidth(90);

    for (qsizetype i = 0 ; i < names.size() ; i++) {
        SidebarModule *module = new SidebarModule(names[i], scrollContent);
        modules.append(module);
        scrollLay->addWidget(module, 0, Qt::AlignHCenter);

        QObject::connect(module, &SidebarModule::pressed, [this, module, i](QPointF offset, QPointF pos){
            emit modulePressed(module, offset, pos, i);
        });
    }

    scrollLay->addStretch();
    scrollLay->setContentsMargins(0, 0, 0, 0);
    lay->addWidget(title, 0, Qt::AlignHCenter);
    lay->addWidget(scroll);
    lay->setContentsMargins(0, 10, 0, 5);
    lay->setSpacing(10);

    setProperty("class", "sidebar");
    title->setProperty("class", "sidebar-title");
    scroll->setProperty("class", "sidebar-scroll");
    scrollContent->setProperty("class", "sidebar-scroll-content");
}

void Sidebar::addModule(QString name)
{
    // TODO
}