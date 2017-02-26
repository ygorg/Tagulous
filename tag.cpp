#include "tag.h"


bool TagListModel::insertRows(int row, int count,
                              const QModelIndex &parent) {
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
    m_tags->append(new Tag("New Tag"));
    //c'est dans la doc de faire ça
    emit endInsertRows();
    return true;
}

Qt::ItemFlags TagListModel::flags(const QModelIndex &index) const {
    return Qt::ItemIsEditable | Qt::ItemIsDragEnabled
            | Qt::ItemIsDropEnabled |QAbstractListModel::flags(index);
}

// !!!!!!!!!!!!!!!!!!!
// !!!!!!!!!!!!!!!!!!
// !!! C'est le best important il faut mettre tout ce qui est utile
// !!!!!!!!!!!!!!!!!!
// !!!!!!!!!!!!!!!!!!!
QStringList TagListModel::mimeTypes () const{
    /* Dit quels type d'info le drop accepte si c'est
     * pas dedans on accepte pas et il ne se passe rien
     * ça dit a Qt ce qu'on accepte exclusivement */
    QStringList qstrList;
    /* ce qui nous interesse c'est le nom des fichiers */
    qstrList.append("text/uri-list");
    return qstrList;
}

Qt::DropActions TagListModel::supportedDropActions() const {
    return Qt::CopyAction;
    //Là vraiment aucune idée vraiment genre la doc n'est d'aucune utilité
}

bool TagListModel::dropMimeData(
        const QMimeData *data, Qt::DropAction action,
        int row, int column, const QModelIndex &parent) {
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

//Faire un diagramme UML pour pas se perdre
//Faire le paper prototype

//TODO faire une classe qui hérite de QList<Tag *>
// et qui représente les Tags
// pour avoir un slot requestedAddFiles(int row, QList<TagFile *>)

//Faire un model pour les QList<TagFile *>
// pour ensuite les afficher dans une listView
// pour la partir où afficher les fichiers

//Faire des fonctions pour la persistance
// y a une giga fonction qui request un endroit pour stocker les fichiers
// ce serais cool de l'utiliser
// genre classe::toXML ou n'importe quel format
// et du coup classe::fromXML ou n'importe quel format

//Comment changer l'affichage des QListView qui est dégueu
// pouvoir mettre des icones devant les tags genre comme sur mac des couleurs
// déjà les feuilles de styles c'est pas mal !
//Pouvoir réorganiser les tags
//  de manière jolie genre tu clique et ça "prend" l'item genre il grossis
//  et suis ta souris

////////
/// Slots
////////

void TagListModel::requestedAddTag() {
    insertRow(rowCount(QModelIndex()));
}
