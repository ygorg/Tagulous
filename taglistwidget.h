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
#include <QIdentityProxyModel>
#include <QAbstractItemModel>
#include <QDebug>

#include <QPushButton>
#include <QToolButton>

#include "taglistmodeldropcheckable.h"

class TagListWidget : public QWidget
{
    Q_OBJECT
private:
    // The model to be displayed and its proxy to filter
    TagListModelDropCheckable *_model;
    QAbstractProxyModel *_proxyModel;

    QVBoxLayout *_layout;
    QLineEdit *_searchBox;
    QListView *_view;

    QToolButton *_filterValidateButton;
    bool filterIsOn = false;
public:
    explicit TagListWidget(QWidget *parent=0);
    ~TagListWidget();

    void connectActions(QMap<QString, QAction *> *);
    void setModel(TagListModelDropCheckable *);

signals:
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
