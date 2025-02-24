#include "start.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("应该不会挂科吧");
    QPixmap img(":/src/hinata.png");
    w.setWindowIcon(img);
    w.show();
    return a.exec();
}
