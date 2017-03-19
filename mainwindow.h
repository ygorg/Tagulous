#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListView>
#include <QString>
#include <QStandardPaths>
#include <QDir>
#include <QMenu>
#include <QMenuBar>
#include <QMap>
#include <QMapIterator>
#include <QStackedWidget>
#include <QDebug>

#include "taglist.h"
#include "taglistmodel.h"
#include "taglistmodeldrop.h"
#include "filelistmodel.h"

#include "taglistwidget.h"
#include "filelistwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:

    QStackedWidget *_stackedWidget = new QStackedWidget();
    TagListWidget *_tagListWidget;
    FileListWidget *_fileListWidget;
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

    void createActions();
    void hideWidget();

private slots:
    void addToolBarAction(QString);
    void showFileList(int row);
    void showTagList();

};

#endif // MAINWINDOW_H
