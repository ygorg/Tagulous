#ifndef FILELISTWIDGET_H
#define FILELISTWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QListView>
#include <QLineEdit>
#include <QMenuBar>
#include <QAction>
#include <QMap>

#include <qsortfilterproxymodelfixed.h>
#include <QAbstractItemModel>

#include "filelistmodel.h"


class QListViewDrop : public QListView {
    Q_OBJECT
public:
    QListViewDrop(QWidget *parent=0) : QListView(parent){
        setAcceptDrops(true);
    }
    void dragEnterEvent(QDragEnterEvent *event) {
        if (event->mimeData()->hasFormat("text/uri-list")) {
            event->acceptProposedAction();
        }

    }
    void dragMoveEvent(QDragMoveEvent *event) {
        if (event->mimeData()->hasFormat("text/uri-list")) {
            event->acceptProposedAction();
        }
    }
    void dropEvent(QDropEvent *event)
    {
        emit requestAddFiles(event->mimeData()->urls());
        event->acceptProposedAction();
    }

signals:
    void requestAddFiles(QList<QUrl>);
};

class FileListWidget : public QWidget
{
    Q_OBJECT
private:
    QMap<QString, QAction *> *_actions;

    QVBoxLayout *_layout;

    QLineEdit *_searchBox;
    QListViewDrop *_fileView;

    FileListModel *_fileListModel;
    QSortFilterProxyModel *_proxyModel;
public:
    explicit FileListWidget(QMap<QString, QAction *> *, QWidget *parent=0);

    void connectActions();
    void setModel(FileListModel *);
    FileListModel *getModel();
signals:
    void toolBarAction(QString);
    void viewTagList();

public slots:
    void requestedAddFiles();
    void deleteElement();
    void copyElement();
    void pasteElement();
    void activateFind();

    void previous();
    void openFile();
    void openFileInFinder();
};

#endif // FILELISTWIDGET_H
