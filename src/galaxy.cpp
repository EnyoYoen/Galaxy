#include "galaxy.h"

#include <QDirIterator>
#include <QLibrary>
#include <QFunctionPointer>

typedef QWidget *(*LoadFunction)(QWidget *); // QWidget *load(QWidget *parent)

Galaxy::Galaxy()
    : QWidget()
{
    lay = new QHBoxLayout(this);
    lay->setContentsMargins(0, 0, 0, 0);

    QStringList modulesNames = getModulesNames();
    for (auto moduleName : modulesNames) {
        loadModule(moduleName);
    }

    setMinimumSize(500, 500);
}

QStringList Galaxy::getModulesNames()
{   
    QStringList modulesNames;
    QDirIterator modulesIt(moduleDirName, QStringList() << "*.yml", QDir::Files);
    
    while (modulesIt.hasNext()) {
        QString name = modulesIt.next();
        QStringList nameSplit = name.split(".");                    // |
        nameSplit.removeLast();                                     // |=> TODO : maybe there's a better way
        modulesNames.append(nameSplit.join(".").split("/").last()); // |
    }
    
    return modulesNames; 
}

bool Galaxy::loadModule(QString name)
{   
    QLibrary module(moduleDirName + name + ".glx");
    if (module.load()) {
        LoadFunction load = (LoadFunction)module.resolve("load");
        if (load == nullptr) {
            // TODO : log
        } else {
            QWidget *moduleWidget = load(this);
            lay->addWidget(moduleWidget);
        }

        return true;
    } else {
        // TODO : log

        return false;
    }
}