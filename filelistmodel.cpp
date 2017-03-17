#include "filelistmodel.h"

#include<QDebug>

FileListModel::FileListModel(QList<Tag*> *list, QObject *parent = 0)
    : QAbstractListModel(parent) {
    tagList = list;
    fileList = new QList<TagFile*>;
    for (Tag *tag : *tagList) {
        fileList->append(*tag);
    }
    for (TagFile *file : *fileList) {
        qDebug() << file->getPath();
    }
}

int FileListModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent)
    return fileList->length();
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



