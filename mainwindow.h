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
#include <QMap>
#include <QMapIterator>

#include "taglist.h"
#include "taglistmodel.h"
#include "taglistmodeldrop.h"
#include "filelistmodel.h"

#include "taglistwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:

    TagListWidget *_tagListWidget;
    //FileListWidget *_fileListWidget;
    QMap<QString, QAction *> *_actions = new QMap<QString, QAction *>;

    QToolBar *_toolbar = new QToolBar(this);
    QMenuBar *_menuBar = new QMenuBar(0);
    QMenu *_menu = new QMenu(tr("File"));

    TagList *_tagList;
    TagListModel *_tagListModel;

    QString _path = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
    QString _fileName = "save.xml";

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QAction *getAction(QString);

    void showTagList();
    void createActions();

private slots:
    void addToolBarAction(QString);
    void addMenuAction(QString);

};

#endif // MAINWINDOW_H
