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

#include "tag.h"
#include "taglistmodel.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QList<Tag *> *tagList;
    TagListModel *tagListModel;
    QListView *listView;


public:
    explicit MainWindow(QWidget *parent = 0);

};

#endif // MAINWINDOW_H
