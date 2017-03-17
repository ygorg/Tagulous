#include "filelistmodel.h"

#include<QDebug>

FileListModel::FileListModel(QList<Tag*> *list, QObject *parent)
    : QAbstractListModel(parent) {
    _tagList = list;
}

FileListModel::FileListModel(Tag *tag, QObject *parent)
    : QAbstractListModel(parent) {
    _tagList = new QList<Tag *>();
    _tagList->append(tag);

}

int FileListModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent)
    int length = 0;
    for (Tag *tag : *_tagList) {
        length += tag->length();
    }
    return length;
}

QVariant FileListModel::data(const QModelIndex &index, int role) const {
    if (role == Qt::DisplayRole) {
        int length = 0;
        for (Tag *tag : *_tagList) {
            if (index.row() - length < tag->length()) {
                return tag->at(index.row() - length)->getName();
            }
            length += tag->length();
        }

    } else if (role == Qt::DecorationRole) {
        int length = 0;
        for (Tag *tag : *_tagList) {
            if (index.row() - length < tag->length()) {
                return tag->at(index.row() - length)->getIcon();
            }
            length += tag->length();
        }

    }
    return QVariant();
}

bool FileListModel::setData(const QModelIndex &index, const QVariant &value,
                            int role) {
    Q_UNUSED(index)
    Q_UNUSED(value)
    Q_UNUSED(role)
    // on n'est rien censé pouvoir modifier
    return false;
}



