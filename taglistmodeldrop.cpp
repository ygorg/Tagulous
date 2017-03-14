#include "taglistmodeldrop.h"

TagListModelDrop::TagListModelDrop(TagList *tagList, QObject *parent=0)
    : TagListModel(tagList, parent)
{}

Qt::ItemFlags TagListModelDrop::flags(const QModelIndex &index) const {
    if (!index.isValid())
        return TagListModel::flags(index)
                | Qt::ItemIsDropEnabled;
    else
        return TagListModel::flags(index)
                | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled;
}

Qt::DropActions TagListModelDrop::supportedDropActions() const {
    return Qt::CopyAction;
}

QStringList TagListModelDrop::mimeTypes() const {
    /* Dit quels type d'info le drop accepte si c'est
     * pas dedans on accepte pas et il ne se passe rien
     * ça dit a Qt ce qu'on accepte exclusivement */
    QStringList types;
    /* ce qui nous interesse c'est le nom des fichiers */
    types << "text/uri-list";
    return types;
}

bool TagListModelDrop::canDropMimeData(const QMimeData *data, Qt::DropAction action,
                  int row, int column, const QModelIndex &parent) const {


    if (action == Qt::IgnoreAction)
        return true;

    if (!data->hasFormat("text/uri-list"))
        return false;

    if (column > 0)
        return false;

    if (!parent.isValid())
        return false;

    return true;
}

bool TagListModelDrop::dropMimeData(const QMimeData *data, Qt::DropAction action,
                  int row, int column, const QModelIndex &parent) {
    /*que faire si des données sont droppés*/

    if (action == Qt::IgnoreAction)
        return true;

    if (!data->hasFormat("text/uri-list"))
        return false;

    if (column > 0)
        return false;

    if (parent.isValid())
        row = parent.row();
    else
        return false;


    Tag *tag = m_tags->at(row);

    QList<QUrl> files = data->urls();
    QList<TagFile *> list;

    //Pour chaque url droppé on crée un TagFile qu'on ajoute au tag
    for (QUrl url : files) {
        tag->append(new TagFile(url.fileName()));
    }

    return true;
}
