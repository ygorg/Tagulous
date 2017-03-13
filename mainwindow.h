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

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QList<Tag *> *tagList;
    TagListModel *tagListModel;
    QListView *listView;

    QListView *listView2;

    bool sideBarIsShown = true;


public:
    explicit MainWindow(QWidget *parent = 0);

private slots:
    void toggleSideBar();

};

#endif // MAINWINDOW_H
