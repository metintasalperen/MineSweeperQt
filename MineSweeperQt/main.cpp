#include "MineSweeperWidgetCls.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    MineSweeperWidgetCls w;
    w.setWindowTitle("Mine Sweeper");
    w.setWindowIcon(QIcon(TILE_BOMB));
    w.show();
    return a.exec();
}
