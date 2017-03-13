#include "filelistmodel.h"

FileListModel::FileListModel(QList<Tag*> *list, QObject *parent = 0)
    : QAbstractListModel(parent) {
    tagList = list;

    fileList = new QList<TagFile*>;
    for (Tag *tag : *tagList) {
        fileList->append(*tag);
    }
}

int FileListModel::rowCount(const QModelIndex &parent) const {
    int size = 0;
    for(Tag *tag : *tagList) {
        size += tag->length();
    }
    return size;
}

QVariant FileListModel::data(const QModelIndex &index, int role) const {
    if (role == Qt::DisplayRole) {
        return fileList->at(index.row())->getName();
    } else if (role == Qt::DecorationRole) {
        return fileList->at(index.row())->getIcon();
    } else if (role == Qt::SizeHintRole) {
        return QSize(10, 30);
    }
    return QVariant();
}

bool FileListModel::setData(const QModelIndex &index, const QVariant &value,
                            int role) {
    // on n'est rien censé pouvoir modifier
    return false;
}

