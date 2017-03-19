#ifndef TAGLISTMODELDROP_H
#define TAGLISTMODELDROP_H

#include "taglistmodel.h"

class TagListModelDrop : public TagListModel {
    //This model add support for dropping files on tags
public:
    TagListModelDrop(TagList *tagList, QObject *parent=0);

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    Qt::DropActions supportedDropActions() const override;

    QStringList mimeTypes() const override;

    bool canDropMimeData(const QMimeData *data, Qt::DropAction action,
                      int row, int column, const QModelIndex &parent) const override;
    bool dropMimeData(const QMimeData *data, Qt::DropAction action,
                      int row, int column, const QModelIndex &parent) override;
};

#endif // TAGLISTMODELDROP_H
