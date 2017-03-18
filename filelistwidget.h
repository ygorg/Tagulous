#ifndef FILELISTWIDGET_H
#define FILELISTWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QListView>
#include <QLineEdit>
#include <QMenuBar>
#include <QAction>
#include <QMap>

#include <QAbstractItemModel>

#include "filelistmodel.h"

class FileListWidget : public QWidget
{
    Q_OBJECT
private:
    QMap<QString, QAction *> *_actions;

    QVBoxLayout *_layout;

    QLineEdit *_searchBox;
    QListView *_fileView;

    FileListModel *_fileListModel;
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
