﻿#include "src/ui/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFont f("Microsoft Yahei",10);
    a.setFont(f);
    MainWindow w;
    w.show();
    return a.exec();
}
