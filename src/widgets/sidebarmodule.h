#ifndef SIDEBAR_MODULE
#define SIDEBAR_MODULE

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QMouseEvent>

class SidebarModule : public QWidget
{
    Q_OBJECT
public:
    SidebarModule(QString name, QWidget *parent); // TODO : use a YAML object representing the module config later (for example to add an icon)
                                 // or an ID (like in To-Do lists module with the manager) of a config object  

signals:
    void pressed(QPointF offset, QPointF pos);

private:
    QHBoxLayout *lay = nullptr;
    QLabel *title = nullptr;
    
    virtual void mousePressEvent(QMouseEvent *e);
};

#endif