#include "sidebartab.h"
#include "clickable.h"
#include "../tools/logger.h"

#include <iostream>

SidebarTab::SidebarTab(QString name, QStringList& elementsTitle, std::vector<std::function<void()>> clicHandlers, QWidget *p)
    : QWidget(p)
{
    lay = new QVBoxLayout(this);
    tabHeader = new QWidget(this);
    tabHeaderLay = new QHBoxLayout(tabHeader);
    icon = new QLabel(tabHeader);
    title = new QLabel(name, tabHeader);
    dropdownIcon = new QPushButton(tabHeader);
    elements = new QWidget(this);
    elementsLay = new QVBoxLayout(elements);
    
    title->setProperty("class", QString("title"));
    icon->setProperty("class", QString("tab-icon-closed"));

    tabHeaderLay->addWidget(icon);
    tabHeaderLay->addWidget(title);
    tabHeaderLay->addWidget(dropdownIcon);

    QObject::connect(dropdownIcon, &QPushButton::clicked, [this, p]() {
        show = !show;
        show ? elements->show() : elements->hide();
        icon->setProperty("class", QString("tab-icon-") + (show ? "opened" : "closed"));
    });

    for (qsizetype i = 0 ; i < elementsTitle.size() ; i++) {
        Clickable *element = new Clickable([clicHandlers, i](QMouseEvent *e) { clicHandlers[i](); }, elements);
        QVBoxLayout *elementLay = new QVBoxLayout(element);
        QLabel *elementTitle = new QLabel(elementsTitle[i]);

        elementLay->addWidget(elementTitle);
        elementsLay->addWidget(element);
        elementsVec.push_back(element);
    }
    elements->hide();

    lay->addWidget(tabHeader);
    lay->addWidget(elements);
    lay->addStretch();

    name.replace(' ', '-');
    name = name.toLower();
    setProperty("class", name + "-tab");
}