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
#include <QPushButton>
#include <QDebug>


#include "taglistmodeldropcheckable.h"

class TagListWidget : public QWidget
{
    Q_OBJECT
private:
    QMap<QString, QAction *> *_actions;

    QVBoxLayout *_layout;

    QLineEdit *_searchBox;
    QListView *_tagView;

    QPushButton *_filterValidateButton;

    TagListModelDropCheckable *_tagListModel;
    QAbstractProxyModel *_proxyModel;

    bool filterIsOn = false;
public:
    explicit TagListWidget(TagListModelDropCheckable *, QMap<QString, QAction *> *, QWidget *parent=0);
    ~TagListWidget();
    void connectActions();

signals:
    void toolBarAction(QString);
    void viewFileList(QModelIndexList *);

public slots:
    void addElement();
    void deleteElement();
    void copyElement();
    void pasteElement();
    void activateFind();

    void filterTags();
    void requestedFilter();
    void renameElement();
    void doubleClicked(QModelIndex);
};

#endif // TAGLISTWIDGET_H
