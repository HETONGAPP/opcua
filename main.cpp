#include "mainwindow.h"
#include <QOpcUaClient>
#include <QOpcUaNode>
#include <QtOpcUa>
#include <QDebug>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
