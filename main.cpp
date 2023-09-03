#include "src/ui/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
#ifdef _WIN32
    QFont f("Microsoft Yahei",10);
    a.setFont(f);
#endif
    MainWindow w;
    w.show();
    return a.exec();
}
