#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyleSheet("QListView {"
                    "   background-color: transparent;"
                    "   border: 0;"
                    "   font: 16pt;"
                    "}"
                    "QListView:item:hover {"
                    "   background: rgb(200, 200, 200, 100);"
                    "}"
                    "QListView:item:selected {"
                    "   background: rgb(200, 200, 200, 150);"
                    "   color: rgb(0, 0, 0);"
                    "}"
                    "QLineEdit#searchLineEdit {"
                    "   margin: 5 10 5 10;"
                    "}");
    a.setAttribute(Qt::AA_UseHighDpiPixmaps);
    a.setAttribute(Qt::AA_DontShowIconsInMenus);
    a.setAttribute(Qt::AA_EnableHighDpiScaling);

    MainWindow w;
    w.setMinimumWidth(280);
    w.show();

    return a.exec();
}
