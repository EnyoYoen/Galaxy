#ifndef TODOLIST
#define TODOLIST

#include "tools/json.h"
#include "widgets/list.h"
#include "widgets/sidebartab.h"

#include <QVector>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QScrollArea>
#include <QLabel>
#include <QPushButton>

#include <vector>

class ToDoList : public QWidget
{
    Q_OBJECT
public:
    ToDoList(QWidget *p);

private slots:
    void addList();

private:
    void createHomeList(Id i);
    void createSidebar();
    void loadConfig();

    void openList(Id id);
    void openHomePage();
    void updateLists(int w);

    virtual void showEvent(QShowEvent *);
    virtual void closeEvent(QCloseEvent *);

    // Home page
    QHBoxLayout *lay = nullptr;
    QScrollArea *scrollList = nullptr;
    QWidget *scrollContent = nullptr;
    QVBoxLayout *scrollLay = nullptr;
    QWidget *listsContainer = nullptr;
    QGridLayout *listsLay = nullptr;
    QLabel *scrollTitle = nullptr;
    QPushButton *newListButton = nullptr;
    PopUp *popup = nullptr;
    QList<Clickable *> homeLists;
    QList<QLabel *> homeListLabels;
    bool homeShown = true;

    // Sidebar
    QWidget *sidebar = nullptr;
    QVBoxLayout *sidebarLay = nullptr;
    QWidget *header = nullptr;
    QHBoxLayout *headerLay = nullptr;
    QLabel *title = nullptr;
    QScrollArea *sbContent = nullptr;
    QPushButton *sbHider = nullptr;
    QWidget *sbContainer = nullptr;
    QVBoxLayout *sbContainerLay = nullptr;
    bool sbOpen = true;

    // Lists
    QList<List *> lists;
    List *listShown = nullptr;
};

#endif