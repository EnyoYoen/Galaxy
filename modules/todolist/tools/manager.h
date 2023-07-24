#include "json.h"
#include "def.h"

#include <QStringList>
#include <QMap>

class Manager
{

public:
    static void load();
    static void save();

    static void viewList(Id listId);
    static void removeList(Id list);
    static void replaceList(Id listId, JList list);
    static Id addList(JList list);
    static JList getList(Id list);
    static QList<Id> getLists();

    static void setIndexSublist(Id list, Id sublist, size_t index);
    static void removeSublist(Id list, Id sublist);
    static void replaceSublist(Id list, Id sublistId, JSublist sublist);
    static Id addSublist(Id list, JSublist sublist);
    static JSublist getSublist(Id list, Id sublist);
    static QList<Id> getSublists(Id list);

    static void setIndexElement(Id list, Id sublist, Id element, size_t index);
    static void removeElement(Id list, Id sublist, Id element);
    static void replaceElement(Id list, Id sublist, Id elementId, JElement element);
    static Id addElement(Id list, Id sublist, JElement element);
    static JElement getElement(Id list, Id sublist, Id element);
    static QList<Id> getElements(Id list, Id sublist);

    static QStringList getRecents();
    
private:
    static QMap<Id, JList> lists; // {id: list}
    static QMap<Id, QList<Id>> sublistsOrder; // {listId: [sublistId, ...]}
    static QMap<Id, QMap<Id, QList<Id>>> elementsOrder; // {listId: {sublistId: [elementId, ...]}}
    static QStringList recent;
    static QString filepath;
};