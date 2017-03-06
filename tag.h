#ifndef TAG_H
#define TAG_H

#include <QColor>
#include <QString>
#include <QList>
#include <QAbstractListModel>
#include <QDebug>
#include <QMimeData>

#include <QPixmap>
#include <QPainter>

class TagFile : public QObject {
/* Représente un fichier dans un Tag
 * On sait jamais si il faudra des membres
 * ou des méthodes en plus mieux vaux faire une classe direct */
  Q_OBJECT
private:
    QString m_filePath;
public:
    explicit TagFile(QString filePath) : QObject() {
        m_filePath = filePath;
    }

    QString getPath() {
        return m_filePath;
    }

};

class Tag : public QList<TagFile *> {
/* Un tag c'est avant tout une liste de fichier
 * avec une couleur (pour le cercle mais c'est a voir)*/
private:
    QString m_tagName;
    QColor m_color;
    QPixmap m_bullet;
public:
    explicit Tag(QString tagName) : QList<TagFile *>() {
        m_tagName = tagName;
        m_color = QColor(0, 0, 0);
        m_bullet = QPixmap(100, 100);
    }

    void setBulletColor(QColor color) {
        this->m_color = color;
        m_bullet.fill(QColor(0, 0, 0, 0));

        QPainter *paint = new QPainter(&m_bullet);
        m_bullet.setDevicePixelRatio(2);
        QPen pen;
        pen.setColor(m_color);
        pen.setWidth(10);
        paint->setPen(pen);
        paint->setBrush(m_color.lighter(110));
        paint->drawEllipse(QPoint(m_bullet.width()/2, m_bullet.height()/2), 45, 45);
    }

    QPixmap getBullet() {
        return m_bullet.scaled(30, 30);
    }

    QString getName() {
        return m_tagName;
    }

    void setName(QString value) {
        m_tagName = value;
    }
};

class TagListModel : public QAbstractListModel {
/* Un modele qui fait l'interface entre une liste de Tag
 * et Qt pour gerer l'affichage et tout
 * La on hérite du QAbstractListModel parce qu'on veut
 * représenter une liste de tag */
    Q_OBJECT
private:
    QList<Tag *> *m_tags;

public:
    TagListModel(QList<Tag *> *tagList, QObject *parent=0)
        : QAbstractListModel(parent) {
        m_tags = tagList;
    }
    int rowCount(const QModelIndex &parent) const override {
        /* La base du model : combien d'éléments a afficher*/
        Q_UNUSED(parent)
        return m_tags->length();
    }
    QVariant data(const QModelIndex &index, int role) const override {
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
    bool setData(const QModelIndex &index, const QVariant &value, int role) override {
        /* Pareil que data mais pour set la valeur au lieu de la get */
        if (role == Qt::EditRole && value != "") {
            /* en gros si on modifie le nom d'un tag et qu'on le met a ""
             * ben on fait rien */
            m_tags->at(index.row())->setName(value.toString());
            return true;
        }
        return false; /* On a pas modifié la valeur */
    }

    bool insertRows(int row, int count, const QModelIndex &parent) override;
    /* Ce qui se passe si on ajoute count ligne a l'indice row */

    Qt::ItemFlags flags(const QModelIndex &index) const override;
    /* renvoie des infos sur les actions possibles sur l'élement */

    Qt::DropActions supportedDropActions() const override;
    /* ça je sais pas trop mais c'est requis pour drop des fichiers */

    QStringList mimeTypes() const override;
    /*voir le .cpp*/

    bool dropMimeData(const QMimeData *data, Qt::DropAction action,
                      int row, int column, const QModelIndex &parent) override;
    /*que faire si des données sont droppés*/
public slots:
    void requestedAddTag();
signals:
};

#endif // TAG_H
