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
#include <QIdentityProxyModel>
#include <QAbstractItemModel>
#include <QMimeData>
#include <QFileDialog>
#include <QDebug>

#include <QDesktopServices>
#include <QMessageBox>

#include "filelistmodel.h"


class QListViewDrop : public QListView {
    // We extend QListView to allow dropping files in it
    Q_OBJECT
public:
    QListViewDrop(QWidget *parent=0)
        : QListView(parent) {
        setAcceptDrops(true);
    }
    void dragEnterEvent(QDragEnterEvent *event) {
        if (event->mimeData()->hasFormat("text/uri-list"))
            event->acceptProposedAction();
    }
    void dragMoveEvent(QDragMoveEvent *event) {
        if (event->mimeData()->hasFormat("text/uri-list"))
            event->acceptProposedAction();
    }
    void dropEvent(QDropEvent *event) {
        emit requestAddFiles(event->mimeData()->urls());
        event->acceptProposedAction();
    }
signals:
    void requestAddFiles(QList<QUrl>);
};

class FileListWidget : public QWidget {
    Q_OBJECT
private:
    // The model to be displayed and its proxy to filter
    FileListModel *_model;
    QAbstractProxyModel *_proxyModel;

    QVBoxLayout *_layout;
    QLineEdit *_searchBox;
    QListViewDrop *_view;

public:
    explicit FileListWidget(QWidget *parent=0);
    ~FileListWidget();

    void connectActions(QMap<QString, QAction *> *);
    void setModel(FileListModel *);

signals:
    void viewTagList();

public slots:
    void addElement();
    void deleteElement();
    void copyElement();
    void pasteElement();
    void activateFind();

    void previous();
    void requestOpenFile();
    void requestOpenFile(QModelIndex index);
    void requestOpenFileInFinder();
};

#endif // FILELISTWIDGET_H
