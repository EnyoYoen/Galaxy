#include "json.h"
#include "def.h"

#include <QStringList>
#include <QMap>

class Manager
{

public:
    static void load();
    static void save();

    static void removeList(Id list);
    static void replaceList(Id listId, JList list);
    static Id addList(JList list);
    static JList getList(Id list);
    static QList<Id> getLists();

    static void removeSublist(Id list, Id sublist);
    static void replaceSublist(Id list, Id sublistId, JSublist sublist);
    static Id addSublist(Id list, JSublist sublist);
    static JSublist getSublist(Id list, Id sublist);
    static QList<Id> getSublists(Id list);

    static void removeElement(Id list, Id sublist, Id element);
    static void replaceElement(Id list, Id sublist, Id elementId, JElement element);
    static Id addElement(Id list, Id sublist, JElement element);
    static JElement getElement(Id list, Id sublist, Id element);
    static QList<Id> getElements(Id list, Id sublist);

    static QStringList getRecents();
    
private:
    static QMap<Id, JList> lists; // {id: list}
    static QStringList recent;
    static QString filepath;
};