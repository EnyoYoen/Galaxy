#include "../tools/json.h"

#include <QJsonArray>

JElement::JElement(QJsonObject j)
    : name(j["name"].toString()), content(j["content"].toString()) 
{}

JElement::JElement(QString m_name, QString m_content) : name(m_name), content(m_content) {}

JElement::JElement() {}

JSublist::JSublist(QJsonObject j)
    : title(j["title"].toString())
{
    auto jarray = j["elements"].toArray();
    for (Id i = 0 ; i < (Id)jarray.size() ; i++)
        elements.insert(i, JElement(jarray[i].toObject()));
}

JSublist::JSublist(QString m_title) : title(m_title) {}

JSublist::JSublist() {}

JList::JList(QJsonObject j)
    : type((Type)j["type"].toInt()), priority(j["priority"].toInt()), title(j["title"].toString()),
      viewTimestamp(QDateTime::fromSecsSinceEpoch(j["view_timestamp"].toInteger())) 
{
    auto jarray = j["sublists"].toArray();
    for (Id i = 0 ; i < (Id)jarray.size() ; i++)
        sublists.insert(i, JSublist(jarray[i].toObject()));
}

JList::JList(QString m_title, Type m_type, int m_priority) : title(m_title), type(m_type), priority(m_priority) {}

JList::JList() : type(None) {}