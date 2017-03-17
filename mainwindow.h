#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListView>
#include <QString>
#include <QStandardPaths>
#include <QDir>
#include <QDebug>
#include <QMenu>
#include <QMenuBar>

#include "taglist.h"
#include "taglistmodel.h"
#include "taglistmodeldrop.h"
#include "filelistmodel.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    TagList *tagList;
    TagListModel *tagListModel;
    FileListModel *fileListModel;

    QListView *listView;
    QListView *listView2;

    bool sideBarIsShown = true;

    QString path = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
    QString fileName = "save.xml";

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void createActions();

private slots:
    void toggleSideBar();
    void deleteElement();
    void renameElement();
    void copyElement();
    void pasteElement();
    void selectTags();
    void doubleCLicked(QModelIndex index);

};

#endif // MAINWINDOW_H
