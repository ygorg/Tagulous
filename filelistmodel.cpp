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

QHash<int,QByteArray> FileListModel::roleNames() const {
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    roles[MyRoles::PathRole] = "role_path";
    return roles;
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
    } else if (role == MyRoles::PathRole) {
        int length = 0;
        for (Tag *tag : *_tagList) {
            if (index.row() - length < tag->length()) {
                return tag->at(index.row() - length)->getPath();
            }
            length += tag->length();
        }
    }
    return QVariant();
}

bool FileListModel::removeRows(int row, int count,
                const QModelIndex &parent) {
    if (parent.isValid())
        row = parent.row();

    //c'est dans la doc de faire ça
    emit beginRemoveRows(parent, row, row+count);
    //et voilà ce qu'on fait vraiment

    int length = 0;
    for (Tag *tag : *_tagList) {
        if (count == 0) {
            return true;
        }
        while (row - length < tag->length() && count > 0) {
            tag->removeAt(row - length);
            count -=1;
            row += 1;
        }
        length += tag->length();
    }
    //c'est dans la doc de faire ça
    emit endRemoveRows();
    return true;
}

Qt::ItemFlags FileListModel::flags(const QModelIndex &index) const {
/* renvoie des infos sur les actions possibles sur l'élement */
    return QAbstractListModel::flags(index);
}


