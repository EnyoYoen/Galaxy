#include "manager.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

QMap<Id, JList> Manager::lists;
QStringList Manager::recent;
#ifdef DL
QString Manager::filepath = "build/modules/cache/todolists.json";
#else
QString Manager::filepath = "todolists.json";
#endif

void Manager::load()
{
    QFile jsonFile(filepath);
    jsonFile.open(QIODevice::ReadOnly);

    if (jsonFile.isOpen()) {
        QJsonObject j = QJsonDocument::fromJson(jsonFile.readAll()).object();

        QJsonArray jlists = j["lists"].toArray();
        for (size_t i = 0 ; i < jlists.count() ; i++) {
            lists.insert(i, JList(jlists[i].toObject()));
        }
        for (auto recentList : j["recent"].toArray()) {
            recent.append(recentList.toString());
        }
    }
}

void Manager::save()
{
    QJsonObject jsave;
    QJsonArray jlists;
    QJsonArray jrecent;

    for (auto list : lists) {
        QJsonObject jlist;
        jlist.insert("type", (int)list.type);
        jlist.insert("priority", list.priority);
        jlist.insert("title", list.title);
        jlist.insert("view_timestamp", list.viewTimestamp.toSecsSinceEpoch());

        QJsonArray jsublists;
        for (auto sublist : list.sublists) {
            QJsonObject jsublist;
            jsublist.insert("title", sublist.title);

            QJsonArray jelements;
            for (auto element : sublist.elements) {
                QJsonObject jelement;
                jelement.insert("name", element.name);
                jelement.insert("content", element.content);
                jelements.append(jelement);
            }
            jsublist.insert("elements", jelements);
            jsublists.append(jsublist);
        }
        jlist.insert("sublists", jsublists);
        jlists.append(jlist);
    }

    for (auto title : recent) {
        jrecent.append(QJsonValue(title));
    }

    jsave.insert("recent", jrecent);
    jsave.insert("lists", jlists);
    
    QFile jsonFile(filepath);
    jsonFile.open(QIODevice::WriteOnly);
    jsonFile.write(QJsonDocument(jsave).toJson(QJsonDocument::Compact));
}

void Manager::removeList(Id list)
{
    lists.remove(list);
    save();
}

void Manager::replaceList(Id listId, JList list)
{
    lists.remove(listId);
    lists.insert(listId, list);
    save();
}

Id Manager::addList(JList list)
{
    Id id = (lists.size() == 0 ? 0 : lists.lastKey() + 1); // TODO : fill available previous ids before adding one ?
    lists.insert(id, list);
    save();
    return id;
}

JList Manager::getList(Id id)
{
    return lists[id];
}

QList<Id> Manager::getLists()
{
    return lists.keys();
}


void Manager::removeSublist(Id list, Id sublist)
{
    lists[list].sublists.remove(sublist);
    save();
}

void Manager::replaceSublist(Id list, Id sublistId, JSublist sublist)
{
    lists[list].sublists.remove(sublistId);
    lists[list].sublists.insert(sublistId, sublist);
    save();
}

Id Manager::addSublist(Id list, JSublist sublist)
{
    auto sublists = lists[list].sublists;
    Id id = (sublists.size() == 0 ? 0 : sublists.lastKey() + 1); // TODO : fill available previous ids before adding one ? Maybe create an Id class
    sublists.insert(id, sublist);
    lists[list].sublists = sublists;
    save();
    return id;
}

JSublist Manager::getSublist(Id list, Id sublist)
{
    return lists[list].sublists[sublist];
}

QList<Id> Manager::getSublists(Id list)
{
    return lists[list].sublists.keys();
}


void Manager::removeElement(Id list, Id sublist, Id element)
{
    lists[list].sublists[sublist].elements.remove(element);
    save();
}

void Manager::replaceElement(Id list, Id sublist, Id elementId, JElement element)
{
    lists[list].sublists[sublist].elements.remove(elementId);
    lists[list].sublists[sublist].elements.insert(elementId, element);
    save();
}

Id Manager::addElement(Id list, Id sublist, JElement element)
{
    auto elements = lists[list].sublists[sublist].elements;
    Id id = (elements.size() == 0 ? 0 : elements.lastKey() + 1); // TODO : fill available previous ids before adding one ? Maybe create an Id class
    lists[list].sublists[sublist].elements.insert(id, element);
    save();
    return id;
}

JElement Manager::getElement(Id list, Id sublist, Id element)
{
    return lists[list].sublists[sublist].elements[element];
}

QList<Id> Manager::getElements(Id list, Id sublist)
{
    return lists[list].sublists[sublist].elements.keys();
}


QStringList Manager::getRecents()
{
    return recent;
}