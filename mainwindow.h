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
#include <QModelIndexList>

#include "taglist.h"
#include "taglistmodeldropcheckable.h"
#include "filelistmodel.h"

#include "taglistwidget.h"
#include "filelistwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:

    // The two principal widgets
    TagListWidget *_tagListWidget;
    FileListWidget *_fileListWidget;

    TagList *_tagList; // The class containing all the data
    TagListModelDropCheckable *_tagListModel; // A model for displaying tags

    // Helper widgets
    QStackedWidget *_stackedWidget = new QStackedWidget();
    QToolBar *_toolbar = new QToolBar(this);
    QMenuBar *_menuBar;
    QMenu *_menu = new QMenu(tr("File"));

    // Actions
    QAction *getAction(QString);
    QMap<QString, QAction *> *_actions = new (QMap<QString, QAction *>);

    // Used for persistance
    QString _path = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
    QString _fileName = "save.xml";
    TagList *loadPersistance();
    void savePersistance(TagList *);


    void createActions();
    void hideWidget();

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void showFileList(QModelIndexList *);
    void showTagList();

};

#endif // MAINWINDOW_H
