#ifndef FILELISTMODEL_H
#define FILELISTMODEL_H

#include <QString>
#include <QList>
#include <QIcon>
#include <QAbstractListModel>

#import "tag.h"
#import "tagfile.h"

class FileListModel : public QAbstractListModel {
    Q_OBJECT
private:
    QList<Tag*> *tagList;
    QList<TagFile*> *fileList;
public:
    FileListModel(QList<Tag*> *list, QObject *parent);
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role) override;


};

#endif // FILELISTMODEL_H
