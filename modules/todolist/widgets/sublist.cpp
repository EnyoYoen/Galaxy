#include "sublist.h"

#include "filters.h"
#include "../tools/json.h"
#include "../tools/manager.h"
#include "../tools/logger.h"

#include <iostream>

Sublist::Sublist(Id m_list, Id m_sublist, QWidget *p)
    : list(m_list), sublist(m_sublist), QLabel(p)
{
    JSublist jsublist = Manager::getSublist(list, sublist);

    lay = new QVBoxLayout(this);
    QWidget *titleContainer = new QWidget(this);
    QHBoxLayout *titleLay = new QHBoxLayout(titleContainer);
    renameButton = new IconButton([this]() {
        emit renameButtonClicked();
    }, "pen", titleContainer);
    deleteButton = new IconButton([this]() {
        emit deleteButtonClicked();
    }, "bin", titleContainer);
    title = new QLabel(jsublist.title, this);
    addButton = new QPushButton(this);

    HoverFilter *f = new HoverFilter(
        [this](QEnterEvent *) {
            renameButton->show();
            deleteButton->show();
        },
        [this](QEnterEvent *) {
            renameButton->hide();
            deleteButton->hide();
        });
    titleContainer->installEventFilter(f);

    renameButton->hide();
    deleteButton->hide();
    title->setMinimumHeight(30);

    titleLay->addWidget(renameButton, 0, Qt::AlignVCenter);
    titleLay->addStretch();
    titleLay->addWidget(title, 0, Qt::AlignHCenter);
    titleLay->addStretch();
    titleLay->addWidget(deleteButton, 0, Qt::AlignVCenter);
    lay->addWidget(titleContainer);

    for (auto elementId : Manager::getElements(list, sublist))
        createElement(QString(), QString(), elementId);
    lay->addStretch();
    lay->addWidget(addButton, 0, Qt::AlignHCenter);
    lay->addSpacing(5);
    lay->setSpacing(6);

    title->setProperty("class", "sublist-title");
    addButton->setProperty("class", "sublist-add-button");
    setProperty("class", "sublist");

    QObject::connect(addButton, &QPushButton::clicked, this, &Sublist::newElement);
}

void Sublist::rename(QString name)
{
    title->setText(name);

    JSublist jsublist = Manager::getSublist(list, sublist);
    jsublist.title = name;
    Manager::replaceSublist(list, sublist, jsublist);
}

void Sublist::newElement()
{
    QStringList prompts;
    prompts.append("Name");
    prompts.append("Content");
    emit popupRequest(prompts, "Create the new element", [this](bool cancelled, QStringList prompts) {
        if (!cancelled && !prompts.empty() && !prompts[0].isEmpty())
            createElement(prompts[0], prompts[1], InvalidId);
    });
}

void Sublist::deselect()
{
    // TODO : add border when selected and remove it in deselect
}

bool Sublist::dropElement(Element *element, Id elementId, Id fromSublist, int y)
{
    // TODO : Maybe replace with runtime values?
    #define L_LIMIT_OFFSET -10
    #define H_LIMIT_OFFSET 10 

    if (y >= this->y() + title->pos().y() + title->height() + L_LIMIT_OFFSET && y <= this->y() + addButton->y() + H_LIMIT_OFFSET) { // in the y limits
        int elementHeight = element->height();

        y -= this->y() + title->pos().y() + title->height() + L_LIMIT_OFFSET;
        int pos = y * 2 / (elementHeight + 6) - 1;
        if (pos % 2) 
            pos++;
        if (pos / 2 > elements.size() + 1)
            pos = elements.size() * 2 + 1;
        pos /= 2;

        lay->insertWidget(pos + 1, element);

        JElement jelement = Manager::getElement(list, fromSublist, elementId);
        Manager::removeElement(list, fromSublist, elementId);
        elementId = Manager::addElement(list, sublist, jelement);
        Manager::setIndexElement(list, sublist, elementId, pos);

        return true;
    }
    return false;
}

void Sublist::createElement(QString name, QString content, Id elementId)
{
    int position = lay->count();
    if (elementId == InvalidId) {
        JElement jelement(name, content);
        elementId = Manager::addElement(list, sublist, jelement);
        position -= 3;
    }
    Element *element = new Element(list, sublist, elementId, this);
    lay->insertWidget(position, element);
    elements.append(element);
    QObject::connect(element, &Element::changeButtonClicked, [this, element]() {
        QStringList prompts;
        prompts.append("Name");
        prompts.append("Content");
        emit popupRequest(prompts, "Change the element", [this, element](bool cancelled, QStringList prompts) {
            if (!cancelled && !prompts.empty() && !prompts[0].isEmpty()) {
                element->setNameAndContent(prompts[0], prompts[1]);
            }
        });
    });
    QObject::connect(element, &Element::deleteButtonClicked, [this, element, elementId]() {
        emit popupRequest(QStringList(), "Are you sure?", [this, element, elementId](bool cancelled, QStringList prompts) {
            if (!cancelled) {
                Manager::removeElement(list, sublist, elementId);
                elements.removeAll(element);
                element->deleteLater();
            }
        });
    });

    QObject::connect(element, &Element::pressed, [this, position, element, elementId](QPointF offsetPos, QPointF pos) {
        emit elementPressed(offsetPos, pos, elementId, position, element);
    });
}

void Sublist::mousePressEvent(QMouseEvent *e)
{
    press = true;
    emit pressed(e->position());
}