#include "MineSweeperWidgetCls.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MineSweeperWidgetCls w;
    w.show();
    return a.exec();
}
