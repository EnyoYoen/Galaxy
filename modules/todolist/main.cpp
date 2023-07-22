#include "todolist.h"

#include <QApplication>

extern "C" Q_DECL_EXPORT QWidget *load(QWidget *parent)
{
    return new ToDoList(parent);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ToDoList t(nullptr);
    t.show();

    return a.exec();
}