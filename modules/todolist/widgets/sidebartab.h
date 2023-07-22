#ifndef SIDEBARTAB
#define SIDEBARTAB

#include <QWidget>
#include <QImage>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>

#include <memory>

class SidebarTab : public QWidget
{

public:
    SidebarTab(QString name, QStringList& elementsTitle, std::vector<std::function<void()>> clicHandlers, QWidget *p);

private:
    QVBoxLayout *lay = nullptr;
    QWidget *tabHeader = nullptr;
    QHBoxLayout *tabHeaderLay = nullptr;
    QLabel *icon = nullptr;
    QLabel *title = nullptr;
    QPushButton *dropdownIcon = nullptr;
    QWidget *elements = nullptr;
    QVBoxLayout *elementsLay = nullptr;
    std::vector<QWidget *> elementsVec;
    bool show = false;
};

#endif