#include "todolist.h"
#include "widgets/clickable.h"
#include "widgets/filters.h"
#include "tools/logger.h"
#include "tools/manager.h"

#include <QFile>
#include <QFontDatabase>
#include <QShortcut>

// Replace hasSidebar with a config? (object passed to the module or file)
ToDoList::ToDoList(/*bool hasSidebar, */QWidget *p)
    : QWidget(p)
{
    Manager::load();

    lay = new QHBoxLayout(this);
    scrollList = new QScrollArea(this);
    scrollContent = new QWidget(scrollList);
    scrollLay = new QVBoxLayout(scrollContent);
    listsContainer = new QWidget(scrollContent);
    listsLay = new QGridLayout(listsContainer);
    scrollTitle = new QLabel("Lists", scrollContent);
    newListButton = new QPushButton("Add List", this);
        
    scrollList->setWidget(scrollContent);
    scrollList->setWidgetResizable(true);
    scrollList->setAttribute(Qt::WA_StyledBackground, true);

    /*if (hasSidebar)
        createSidebar();*/ // TODO : sidebar

    scrollLay->addSpacing(10);
    scrollLay->addWidget(scrollTitle, 0, Qt::AlignHCenter);
    scrollLay->addWidget(listsContainer, 0, Qt::AlignHCenter);
    scrollLay->addStretch();
    scrollLay->setSpacing(20);
    auto jlists = Manager::getLists();
    for (auto id : jlists) {
        createHomeList(id); 

        List *list = new List(id, listsContainer);
        list->hide();
        lay->addWidget(list);
        lists.append(list);

        QObject::connect(list, &List::back, this, &ToDoList::openHomePage);
        QObject::connect(list, &List::deleted, [this, list, id]() {
            homeLists.takeAt(lists.indexOf(list))->deleteLater();
            homeListLabels.takeAt(lists.indexOf(list));
            lists.removeAll(list);
            openHomePage();
        });
        QObject::connect(list, &List::renamed, [this, list, id]() {
            homeListLabels[lists.indexOf(list)]->setText(Manager::getList(id).title);
        });
    }

    listsLay->setHorizontalSpacing(5);
    listsLay->setContentsMargins(0, 0, 0, 0);
    scrollList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollLay->setContentsMargins(10, 0, 10, 0);
    lay->addWidget(scrollList);
    lay->setContentsMargins(0, 0, 0, 0);
    
    newListButton->setFixedHeight(30);

    ResizeFilter *f = new ResizeFilter([this](QResizeEvent *e) {
        QSize s = e->size();
        newListButton->move(s.width() - newListButton->width() - 5, s.height() - newListButton->height() - 5);
        if (popup)
            popup->setFixedSize(s);

        updateLists(s.width());
    });
    installEventFilter(f);

    QShortcut *addElementShortcut = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_Plus), this, [this]() {
        if (!homeShown)
            listShown->newElement(); // TODO : not working
    });
    QShortcut *addShortcut = new QShortcut(QKeySequence(Qt::Key_Plus), this, [this]() {
        if (homeShown) {
            addList();
        } else {
            listShown->addSublist();
        }
    });

    if (QFontDatabase::addApplicationFont(":/whitney.otf")) {
        logger.warn("Can't add application font : whitney");
    }

    scrollList->setProperty("class", "scroll-list");
    scrollContent->setProperty("class", "scroll-list-content");
    scrollTitle->setProperty("class", "scroll-list-title");
    newListButton->setProperty("class", "homepage-list-button");
    setProperty("class", "todolist");

    QFile style(":/style.css");
    style.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(style.readAll());
    setStyleSheet(styleSheet);
    
    QObject::connect(newListButton, &QPushButton::clicked, this, &ToDoList::addList);
}

void ToDoList::addList()
{
    QVector<QString> prompts;
    prompts.append("Name");
    popup = new PopUp(prompts, "Name the list", this);
    QObject::connect(popup, &PopUp::result, [this](bool cancelled, QStringList prompts) {
        if (!cancelled && !prompts.isEmpty() && !prompts[0].isEmpty()) {
            size_t i = homeLists.size();
            Id id = Manager::addList(JList(prompts[0], JList::Default, 0));
            createHomeList(i);
            
            List *list = new List(i, this);
            list->hide();
            lay->addWidget(list);
            lists.append(list);

            QObject::connect(list, &List::back, this, &ToDoList::openHomePage);
            QObject::connect(list, &List::deleted, [this, list, id]() {
                size_t index = lists.indexOf(list);
                homeLists.takeAt(index)->deleteLater();
                homeListLabels.takeAt(index);
                lists.removeAll(list);
                openHomePage();
            });
            QObject::connect(list, &List::renamed, [this, list, id]() {
                homeListLabels[lists.indexOf(list)]->setText(Manager::getList(id).title);
            });
        }
        popup->deleteLater();
        popup = nullptr;
    });
}

void ToDoList::createHomeList(Id id)
{
    Clickable *container = new Clickable([this, id](QMouseEvent *e) { openList(id); }, listsContainer);
    QHBoxLayout *containerLay = new QHBoxLayout(container);
    JList list = Manager::getList(id);
    QLabel *listTitle = new QLabel(list.title, container);

    containerLay->addStretch();
    containerLay->addWidget(listTitle, 0, Qt::AlignCenter);
    containerLay->addStretch();

    homeLists.append(container);
    homeListLabels.append(listTitle);
    updateLists(scrollList->width());

    container->setFixedSize(200, 200);
    container->setProperty("class", "scroll-list-element");
    listTitle->setProperty("class", "scroll-list-element-title");
}

void ToDoList::createSidebar()
{
    sidebar = new QWidget(this);
    sidebarLay = new QVBoxLayout(sidebar);
    header = new QWidget(sidebar);
    headerLay = new QHBoxLayout(header);
    sbHider = new QPushButton(header);
    title = new QLabel("To-Do List", header);
    sbContent = new QScrollArea(sidebar);
    sbContainer = new QWidget(sbContent);
    sbContainerLay = new QVBoxLayout(sbContainer);

    sbHider->setProperty("class", "sidebar-hider-opened");
    QObject::connect(sbHider, &QPushButton::clicked, [this]() {
        sbOpen = !sbOpen;
        sbHider->setProperty("class", QString("sidebar-hider-") + (sbOpen ? "opened" : "closed"));
        if (sbOpen) {
            title->show();
            sbContent->show();
        } else {
            title->hide();
            sbContent->hide();
        }
    });

    headerLay->addWidget(title);
    headerLay->addWidget(sbHider);
    sidebarLay->addWidget(header);
    header->setProperty("class", "sidebar-header");

    std::vector<std::function<void()>> recentListsHandlers;
    auto recents = Manager::getRecents();
    for (Id i = 0 ; i < (Id)recents.size() ; i++) {
        recentListsHandlers.push_back([this, i]() { openList(i); });
    }
    SidebarTab *recentLists = new SidebarTab("Recent lists", recents, recentListsHandlers, sbContent);
    sbContainerLay->addWidget(recentLists);
    sbContainerLay->addStretch();
    
    sbContent->setWidget(sbContainer);
    sbContent->setWidgetResizable(true);

    sidebarLay->addWidget(sbContent);
    sidebarLay->addStretch();

    sidebar->setProperty("class", "sidebar");
    lay->addWidget(sidebar);
}


void ToDoList::openList(Id id)
{
    scrollList->hide();
    for (auto list : lists) 
        list->hide();
    listShown = lists[id]; 
    listShown->show();
    homeShown = false;

    Manager::viewList(id);
}

void ToDoList::openHomePage()
{
    for (auto list : lists) 
        list->hide();
    
    scrollList->show();
    updateLists(scrollList->width());
    homeShown = true;
    listShown = nullptr;
}

void ToDoList::updateLists(int w)
{
    for (int i = 0 ; i < listsLay->count() ; i++)
        listsLay->removeItem(listsLay->itemAt(i));
    int r = 0, c = 0;
    for (auto list : homeLists) {
        listsLay->addWidget(list, r, c);
        c++;
        int threshold = (w - 5*c - 2*10 - (sidebar ? sidebar->width() : 0)) / 200;
        if (threshold < c+1) {
            c = 0;
            r++;
        }
    }
}

void ToDoList::showEvent(QShowEvent *e)
{
    updateLists(scrollList->width());
}

void ToDoList::closeEvent(QCloseEvent *)
{
    Manager::save();
}