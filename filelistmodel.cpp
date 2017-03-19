#include "filelistmodel.h"

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

TagFile *FileListModel::getFile(int row)  const{
    int length = 0;
    for (Tag *tag : *_tagList) {
        if (row - length < tag->length()) {
            return tag->at(row - length);
        }
        length += tag->length();
    }
    return nullptr;
}

QVariant FileListModel::data(const QModelIndex &index, int role) const {
    if (role == Qt::DisplayRole) {
        return getFile(index.row())->getName();

    } else if (role == Qt::DecorationRole) {
        return getFile(index.row())->getIcon();

    } else if (role == MyRoles::PathRole) {
        return getFile(index.row())->getPath();

    } else if (role == Qt::SizeHintRole) {
        return QSize(10, 30);

    } else if (role == Qt::FontRole) {
        return QFont("", 12);

    }
    return QVariant();
}

bool FileListModel::removeRows(int row, int count,
                const QModelIndex &parent) {
    if (parent.isValid())
        row = parent.row();

    emit beginRemoveRows(parent, row, row+count);

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

    emit endRemoveRows();
    return true;
}

Qt::ItemFlags FileListModel::flags(const QModelIndex &index) const {
/* renvoie des infos sur les actions possibles sur l'élement */
    return QAbstractListModel::flags(index);
}

void FileListModel::addFiles(QList<QUrl> urls) {
    int len = rowCount();
    emit beginInsertRows(QModelIndex(), len, len + urls.length());

    for (QUrl url : urls) {
        for (Tag *tag : *_tagList) {
            tag->append(TagFile::find(url.url()));
        }
    }

    emit endInsertRows();
}

void FileListModel::addFiles(QStringList urls) {
    int len = rowCount();
    emit beginInsertRows(QModelIndex(), len, len + urls.length());

    for (QString url : urls) {
        for (Tag *tag : *_tagList) {
            tag->append(TagFile::find(url));
        }
    }

    emit endInsertRows();
}

