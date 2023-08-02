#include "galaxy.h"

#include "tools/logger.h"

#include <QDirIterator>
#include <QLibrary>
#include <QFunctionPointer>

typedef QWidget *(*LoadFunction)(QWidget *); // QWidget *load(QWidget *parent)

Galaxy::Galaxy()
    : QWidget()
{
    Logger::setup();

    loadModulesNames();

    lay = new QHBoxLayout(this);
    lay->setContentsMargins(0, 0, 0, 0);

    sidebar = new Sidebar(modulesNames, this);

    modulesContainer = new QWidget(this);
    modulesContLay = new QHBoxLayout(modulesContainer);
    modulesContLay->setContentsMargins(0, 0, 0, 0);
    modulesContLay->setSpacing(0);

    lay->addWidget(sidebar);
    lay->addWidget(modulesContainer);

    if (QFontDatabase::addApplicationFont(":/whitney.otf")) {
        logger.warn("Can't add application font : whitney");
    }

    QFile style(":/galaxy-style.css");
    style.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(style.readAll());
    setStyleSheet(styleSheet);

    setProperty("class", "galaxy");

    setMinimumSize(1000, 800); // TODO : temporary

    QObject::connect(sidebar, &Sidebar::modulePressed, [this](SidebarModule *module, QPointF offset, QPointF pos, int layPos){
        this->module = module;
        moduleDragOffset = offset;
        this->layPos = layPos;

        QPointF origin = pos - sidebar->pos() - offset;

        sidebar->scrollLay->removeWidget(module);
        lay->addWidget(module);
        module->move(origin.x(), origin.y());
        module->setParent(this);
        module->raise();
    });
}

Galaxy::~Galaxy()
{
    Logger::close();
}

void Galaxy::loadModulesNames()
{   
    QDirIterator modulesIt(moduleDirName, QStringList() << "*.yml", QDir::Files);
    
    while (modulesIt.hasNext()) {
        QString name = modulesIt.next();
        QStringList nameSplit = name.split(".");                    // |
        nameSplit.removeLast();                                     // |=> TODO : maybe there's a better way
        modulesNames.append(nameSplit.join(".").split("/").last()); // |
    }
}

bool Galaxy::loadModule(QString name, QPointF pos)
{
    if (!modulesContainer->rect().translated(modulesContainer->pos()).contains(pos.x(), pos.y())
        || (modules.size() != 0 && hoveredModule == nullptr))
        return false;

    QLibrary module(moduleDirName + name + ".glx");
    if (module.load()) {
        LoadFunction load = (LoadFunction)module.resolve("load");
        if (load == nullptr) {
            logger.warn(("Could not find " + name + "'s load function").toStdString());

            return false;
        } else {
            logger.info(("Loading " + name + "...").toStdString());

            QWidget *container = new QWidget(modules.size() == 0 ? modulesContainer : (QWidget *)(hoveredModule->parent()));
            QBoxLayout *containerLay;

            QWidget *moduleContainer = new QWidget(modules.size() == 0 ? modulesContainer : (QWidget *)(hoveredModule->parent()));
            QVBoxLayout *moduleContLay = new QVBoxLayout(moduleContainer);
            QLabel *moduleTitle = new QLabel(name, moduleContainer);
            QWidget *moduleWidget = load(moduleContainer);

            moduleTitle->setContentsMargins(5, 5, 5, 5);

            moduleContLay->addWidget(moduleTitle, 0, Qt::AlignCenter);
            moduleContLay->addWidget(moduleWidget);
            moduleContLay->setContentsMargins(0, 0, 0, 0);
            moduleContLay->setSpacing(0);

            if (modules.size() == 0) {
                modulesContLay->addWidget(moduleContainer);
            } else {
                quint8 area; // 0: top / 1: bottom / 2: left / 3: right
                QRect rect = hoveredModule->rect();
                QPoint center = rect.center();
                int dx = center.x() - hoverPos.x();
                int dy = center.y() - hoverPos.y();
                if (qAbs((float)(dx) * 2 / rect.width()) < qAbs((float)(dy) * 2 / rect.height()))
                    area = dy > 0 ? 0 : 1; 
                else
                    area = dx > 0 ? 2 : 3;

                QLayout *hoveredLayout = static_cast<QWidget *>(hoveredModule->parent())->layout();
                
                containerLay = (area == 0 || area == 1 ? (QBoxLayout *)new QVBoxLayout(container) : (QBoxLayout *)new QHBoxLayout(container));
                containerLay->setSpacing(0);
                containerLay->setContentsMargins(0, 0, 0, 0);
                hoveredLayout->removeWidget(hoveredModule);
                containerLay->addWidget(hoveredModule);
                containerLay->insertWidget((area == 0 || area == 2 ? 0 : 1), moduleContainer);
                hoveredLayout->addWidget(container);
            }

            modules.append(moduleContainer);

            moduleContainer->setProperty("class", "module-container");
            moduleTitle->setProperty("class", "module-title");

            logger.info((name + " loaded").toStdString());

            return true;
        }
    } else {
        logger.warn(("Could not load " + name + "'s library").toStdString());

        return false;
    }
}

void Galaxy::mouseReleaseEvent(QMouseEvent *e)
{
    if (module) {
        for (auto module : modules) {
            QPoint offset = modulesContainer->pos();
            QRect rect = module->rect();
            QWidget *parent = module;
            while (parent->parent() != modulesContainer) {
                offset += parent->pos();
                parent = (QWidget *)parent->parent();
            }
            //qDebug() << offset << rect.translated(offset) << e->scenePosition();
            if (rect.translated(offset).contains(e->scenePosition().x(), e->scenePosition().y())) {
                hoveredModule = module;
                hoverPos = e->pos() - offset;
                break;
            }
        }
        //qDebug() << "";

        if (!sidebar->rect().contains(module->rect().center() + module->pos())) {
            loadModule(modulesNames[layPos], e->scenePosition());
        }
        
        lay->removeWidget(module);
        module->setParent(sidebar);
        sidebar->scrollLay->insertWidget(layPos, module, 0, Qt::AlignHCenter);
        module = nullptr;
    }
}

void Galaxy::mouseMoveEvent(QMouseEvent *e)
{
    if (module) {
        QPointF fpos(e->position() - moduleDragOffset);
        module->move(fpos.x(), fpos.y());
    }
}

void Galaxy::closeEvent(QCloseEvent *e)
{
    Logger::close();
}