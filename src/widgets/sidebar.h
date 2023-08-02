#ifndef SIDEBAR
#define SIDEBAR

#include "sidebarmodule.h"

#include <QWidget>
#include <QLabel>
#include <QScrollArea>
#include <QVBoxLayout>

class Sidebar : public QWidget
{
    Q_OBJECT

    enum class Position {
        Top,
        Right,
        Bottom,
        Left,
    }; // TODO : put sidebar on a side

    enum class Direction {
        Down,
        Right,
        Up,
        Left,
    };

public:
    Sidebar(QStringList names, QWidget *parent/*, Direction dir = Direction::Down*/); // TODO : use a QList of config object instead of just names

    QVBoxLayout *scrollLay = nullptr;

public slots:
    void addModule(QString name);

signals:
    void modulePressed(SidebarModule *module, QPointF offset, QPointF pos, int layPos);

private:
    QVBoxLayout *lay = nullptr;
    QScrollArea *scroll = nullptr;
    QWidget *scrollContent = nullptr;
    QLabel *title = nullptr;
    QList<SidebarModule *> modules;
};

#endif