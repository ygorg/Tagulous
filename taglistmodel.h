#ifndef TAGLISTMODEL_H
#define TAGLISTMODEL_H

#include <QAbstractListModel>
#include <QList>
#include <QAction>
#include <QToolBar>
#include <QHBoxLayout>
#include <QMimeData>

#include "taglist.h"

class TagListModel : public QAbstractListModel {
    Q_OBJECT
protected:
    TagList *_tags;
    Tag *newTag();

public:
    TagListModel(TagList *tagList, QObject *parent);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index,
                 const QVariant &value, int role) override;

    bool insertRows(int row, int count,
                    const QModelIndex &parent = QModelIndex()) override;
    bool removeRows(int row, int count,
                    const QModelIndex &parent = QModelIndex()) override;
    bool moveRows(const QModelIndex &sourceParent, int sourceRow,
                    int count, const QModelIndex &destinationParent,
                    int destinationChild) override;


    Qt::ItemFlags flags(const QModelIndex &index) const override;


public slots:
    void requestedAddTag();
signals:

};

#endif // TAGLISTMODEL_H
