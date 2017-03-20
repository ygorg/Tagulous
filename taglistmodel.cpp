#include "taglistmodel.h"

TagListModel::TagListModel(TagList *tagList, QObject *parent=0)
    : QAbstractListModel(parent) {
    _tags = tagList;
}

int TagListModel::rowCount(const QModelIndex &parent) const {
    /* La base du model : combien d'éléments a afficher*/
    Q_UNUSED(parent)
    return _tags->length();
}

QVariant TagListModel::data(const QModelIndex &index,
                            int role) const {
    /* La deuxieme base :U : si on demande la donnée a afficher
     * a l'index index comment on la récupere, ici c'est facile
     * on a une liste */
    /* role c'est en gros les options d'affichage genre pour changer
     * la police il faut renvoyer une police si le role c'est genre
     * Qt::DisplayFont (en vrai pas du tout mais c'est l'idée)*/
    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        return _tags->at(index.row())->getName();
    } else if (role == Qt::DecorationRole) {
        return _tags->at(index.row())->getBullet();
    } else if (role == Qt::SizeHintRole) {
        return QSize(10, 30);
    }
    return QVariant(); /* La valeur par défaut */
}

bool TagListModel::setData(const QModelIndex &index,
                           const QVariant &value, int role) {
    /* Pareil que data mais pour set la valeur au lieu de la get */
    if (role == Qt::EditRole) {
        /* en gros si on modifie le nom d'un tag et qu'on le met a ""
         * ben on fait rien */
        if (value.toString() == "") {
            _tags->at(index.row())->setName("Tag");
        } else {
            _tags->at(index.row())->setName(value.toString());
        }
        emit dataChanged(index, index);
        return true;
    }
    return false; /* On a pas modifié la valeur */
}

Tag *TagListModel::newTag() {
    // couleurs :   orange :    253,148,38
    //              jaune :     254,203,47
    //              vert :      104,216,69
    //              belu :      42,174,245
    //              violet :    203,119,223
    //              gris :      142,142,145
    //              rouge :     252,61,57
    static QColor defaultColors[] =
            {QColor(253,148,38), QColor(254,203,47), QColor(104,216,69),
            QColor(42,174,245), QColor(203,119,223), QColor(142,142,145),
            QColor(252,61,57)};
    static int defaultColorsIndex = 0;
    static int defaultColorsLength = 7;

    Tag *tag = new Tag(tr("New Tag"));
    tag->setBulletColor(defaultColors[defaultColorsIndex]);
    defaultColorsIndex = (defaultColorsIndex + 1) % defaultColorsLength;
    return tag;
}

bool TagListModel::insertRows(int row, int count,
                              const QModelIndex &parent) {

    /* Ce qui se passe si on ajoute count ligne a l'indice row */
    if (row != rowCount()) {
        /* Si on veut ajouter une ligne pas a la fin on abort */
        return false;
    }
    if (parent.row() != -1) {
        /* si on veut ajouter un row dans un row et pas entre 2 */
        return false;
    }
    //c'est dans la doc de faire ça
    emit beginInsertRows(parent, row, row+count);
    //et voilà ce qu'on fait vraiment
    for (int i = 0; i < count; i++) {
        _tags->append(newTag());
    }
    //c'est dans la doc de faire ça
    emit endInsertRows();
    return true;
}

bool TagListModel::removeRows(int row, int count,
                const QModelIndex &parent) {
    if (row < 0 || row > rowCount()) {
        /* Si on veut ajouter une ligne pas a la fin on abort */
        return false;
    }
    if (parent.row() != -1) {
        /* si on veut ajouter un row dans un row et pas entre 2 */
        return false;
    }
    //c'est dans la doc de faire ça
    emit beginRemoveRows(parent, row, row+count);
    //et voilà ce qu'on fait vraiment
    for (int i = count - 1; i >= 0; i--) {
        _tags->removeAt(i+row);
    }
    //c'est dans la doc de faire ça
    emit endRemoveRows();
    return true;
}

bool TagListModel::moveRows(const QModelIndex &sourceParent, int sourceRow,
                            int count, const QModelIndex &destinationParent,
                            int destinationChild) {

    if (sourceRow < 0 || sourceRow > rowCount()
            || destinationChild < 0 || destinationChild > rowCount()) {
        return false;
    }
    if (sourceParent.row() != -1 || destinationParent.row() != 1) {
        return false;
    }

    for (int i = 0; i < count; i++) {
        _tags->move(sourceRow + i, destinationChild + i);
    }

    return false;
}



Qt::ItemFlags TagListModel::flags(const QModelIndex &index) const {
/* renvoie des infos sur les actions possibles sur l'élement */
    return Qt::ItemIsEditable | QAbstractListModel::flags(index);
}

void TagListModel::requestedAddTag() {
    insertRow(rowCount());
}
