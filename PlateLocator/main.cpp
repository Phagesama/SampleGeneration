#include "platelocator.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PlateLocator w;
    w.show();

    return a.exec();
}
