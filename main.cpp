#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyleSheet("QListView {"
                    "   background-color: transparent;"
                    "   border: 0;"
                    "}"
                    "QListView:item:hover {"
                    "   background: rgb(200, 200, 200, 50)"
                    "}");
    MainWindow w;
    w.show();

    return a.exec();
}
