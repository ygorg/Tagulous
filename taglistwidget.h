#ifndef TAGLISTWIDGET_H
#define TAGLISTWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QListView>
#include <QLineEdit>
#include <QMenuBar>
#include <QAction>
#include <QMap>
#include <qsortfilterproxymodelfixed.h>
#include <QAbstractItemModel>
#include <QDebug>


#include "taglistmodel.h"

class TagListWidget : public QWidget
{
    Q_OBJECT
private:
    QMap<QString, QAction *> *_actions;

    QVBoxLayout *_layout;

    QLineEdit *_searchBox;
    QListView *_tagView;

    QAbstractItemModel *_tagListModel;
    QSortFilterProxyModel *_proxyModel;
public:
    explicit TagListWidget(TagListModel *, QMap<QString, QAction *> *, QWidget *parent=0);
    ~TagListWidget();
    void connectActions();

signals:
    void toolBarAction(QString);
    void viewFileList(int);

public slots:
    void addElement();
    void deleteElement();
    void copyElement();
    void pasteElement();
    void activateFind();

    void filterTags();
    void renameElement();
    void doubleClicked(QModelIndex);
};

#endif // TAGLISTWIDGET_H
