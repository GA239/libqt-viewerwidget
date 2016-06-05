#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //QCommandLineParser commandLineParser;
    //commandLineParser.addHelpOption();
    MainWindow w;
    w.show();

    return a.exec();
}
