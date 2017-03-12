#include "taglistmodel.h"

TagListModel::TagListModel(QList<Tag *> *tagList, QObject *parent=0)
    : QAbstractListModel(parent) {
    m_tags = tagList;
}

int TagListModel::rowCount(const QModelIndex &parent) const {
    /* La base du model : combien d'éléments a afficher*/
    Q_UNUSED(parent)
    return m_tags->length();
}

QVariant TagListModel::data(const QModelIndex &index,
                            int role) const {
    /* La deuxieme base :U : si on demande la donnée a afficher
     * a l'index index comment on la récupere, ici c'est facile
     * on a une liste */
    /* role c'est en gros les options d'affichage genre pour changer
     * la police il faut renvoyer une police si le role c'est genre
     * Qt::DisplayFont (en vrai pas du tout mais c'est l'idée)*/
    if (role == Qt::DisplayRole) {
        return m_tags->at(index.row())->getName();
    } else if (role == Qt::DecorationRole) {
        return m_tags->at(index.row())->getBullet();
    } else if (role == Qt::SizeHintRole) {
        return QSize(10, 30);
    }
    return QVariant(); /* La valeur par défaut */
}

bool TagListModel::setData(const QModelIndex &index,
                           const QVariant &value, int role) {
    /* Pareil que data mais pour set la valeur au lieu de la get */
    if (role == Qt::EditRole && value != "") {
        /* en gros si on modifie le nom d'un tag et qu'on le met a ""
         * ben on fait rien */
        m_tags->at(index.row())->setName(value.toString());
        emit dataChanged(index, index);
        return true;
    }
    return false; /* On a pas modifié la valeur */
}

bool TagListModel::insertRows(int row, int count,
                              const QModelIndex &parent) {
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


    /* Ce qui se passe si on ajoute count ligne a l'indice row */
    if (row != rowCount(QModelIndex())) {
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
    Tag *n_tag = new Tag("New Tag");
    n_tag->setBulletColor(defaultColors[defaultColorsIndex]);
    defaultColorsIndex = (defaultColorsIndex + 1) % defaultColorsLength;

    m_tags->append(n_tag);

    //c'est dans la doc de faire ça
    emit endInsertRows();
    return true;
}


Qt::ItemFlags TagListModel::flags(const QModelIndex &index) const {
/* renvoie des infos sur les actions possibles sur l'élement */
    return Qt::ItemIsEditable | Qt::ItemIsDragEnabled
            | Qt::ItemIsDropEnabled |QAbstractListModel::flags(index);
}

Qt::DropActions TagListModel::supportedDropActions() const {
    /* ça je sais pas trop mais c'est requis pour drop des fichiers */
    return Qt::CopyAction;
    //Là vraiment aucune idée vraiment genre la doc n'est d'aucune utilité
}

QStringList TagListModel::mimeTypes() const {
    /* Dit quels type d'info le drop accepte si c'est
     * pas dedans on accepte pas et il ne se passe rien
     * ça dit a Qt ce qu'on accepte exclusivement */
    QStringList qstrList;
    /* ce qui nous interesse c'est le nom des fichiers */
    qstrList.append("text/uri-list");
    return qstrList;
}

bool TagListModel::dropMimeData(const QMimeData *data, Qt::DropAction action,
                  int row, int column, const QModelIndex &parent) {
    /*que faire si des données sont droppés*/
    Q_UNUSED(action)

    if (row == -1 && column == -1) {
        /* Si le drop se fait sur un element */
        QStringList files;
        QList<TagFile *> list;

        //On récupere les données
        files = data->text().split("\n", QString::SkipEmptyParts);

        //Pour chaque fichier droppé on crée un TagFile
        for (QString filePath : files) {
            list.append(new TagFile(filePath));
        }

        qDebug() << "On Item" << files;
        /* On ajoute les TagFile au Tag */
        m_tags->at(parent.row())->append(list);

        //On affiche le nombre de fichier du tag
        qDebug() << m_tags->at(parent.row())->length();

    } else if (parent.row() == -1 && parent.column() == -1) {
        /* Si le drop se fait entre 2 lignes */
        qDebug() << "Between lines" << data->text();
        return false;
    }
    return true;
}

void TagListModel::requestedAddTag() {
    insertRow(rowCount(QModelIndex()));
}
