#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPainter>
#include <QListView>
#include <QStringListModel>
#include <QStringList>
#include <QListWidget>
#include <QMessageBox>
#include <QDropEvent>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QPushButton>
#include <QVBoxLayout>
#include <QToolBar>


#include "tag.h"
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
