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
    QList<Tag*> *_tagList;
public:
    FileListModel(QList<Tag*> *list, QObject *parent=0);
    FileListModel(Tag *tag, QObject *parent=0);
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role) override;


};

#endif // FILELISTMODEL_H
