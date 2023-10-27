#include "mainwindow.h"
#include "startmainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
   // startMainWindow w;
    w.show();
    return a.exec();
}
