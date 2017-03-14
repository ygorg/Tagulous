#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListView>
#include <QString>
#include <QStandardPaths>
#include <QDir>
#include <QDebug>

#include "taglist.h"
#include "taglistmodel.h"
#include "filelistmodel.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    TagList *tagList;
    TagListModel *tagListModel;

    QListView *listView;
    QListView *listView2;

    bool sideBarIsShown = true;

    QString path = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
    QString fileName = "save.xml";

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void toggleSideBar();

};

#endif // MAINWINDOW_H
