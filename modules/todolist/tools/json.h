#ifndef JSON
#define JSON

#include "../tools/def.h"

#include <QString>
#include <QList>
#include <QJsonObject>

class JElement
{
public:
    JElement(QJsonObject j);
    JElement(QString name, QString content);
    JElement();

    QString name;
    QString content;
};

class JSublist
{
public:
    JSublist(QJsonObject j);
    JSublist(QString title);
    JSublist();

    QString title;
    QMap<Id, JElement> elements;

};

class JList
{
public:
    enum Type
    {
        None,
        Default,
        Calendar,

    };

    JList(QJsonObject j);
    JList(QString title, Type type, int priority);
    JList();

    Type type;
    int priority;
    QString title;
    QDateTime viewTimestamp;
    QMap<Id, JSublist> sublists;
};

#endif