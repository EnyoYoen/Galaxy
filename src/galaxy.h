#include "widgets/sidebar.h"

#include <QMap>
#include <QWidget>
#include <QVBoxLayout>
#include <QFontDatabase>

class Galaxy : public QWidget
{
    Q_OBJECT
public:
    Galaxy();
    ~Galaxy();

private:
    void loadModulesNames();
    bool loadModule(QString name, QPointF pos);

    const QString moduleDirName = "modules/";

    QHBoxLayout *lay = nullptr;
    Sidebar *sidebar = nullptr;

    // Drag and Drop
    SidebarModule *module = nullptr;
    QPointF moduleDragOffset;
    int layPos;

    QStringList modulesNames;
    QList<QWidget *> modules;
    QWidget *modulesContainer = nullptr;
    QBoxLayout *modulesContLay = nullptr;
    QWidget *hoveredModule = nullptr;
    QPointF hoverPos;

    virtual void mouseReleaseEvent(QMouseEvent *e);
    virtual void mouseMoveEvent(QMouseEvent *e);
    virtual void closeEvent(QCloseEvent *e);
};