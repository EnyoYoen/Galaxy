#include "galaxy.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    Galaxy *galaxy = new Galaxy();
    galaxy->show();

    return a.exec();
}