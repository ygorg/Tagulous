#include "tag.h"

Tag::Tag(QString tagName)
                    : QList<TagFile *>() {
    m_tagName = tagName;
    m_color = QColor(0, 0, 0);
    m_bullet = QPixmap(100, 100);
}

void Tag::setBulletColor(QColor color) {
    this->m_color = color;
    m_bullet.fill(QColor(0, 0, 0, 0));

    QPainter *paint = new QPainter(&m_bullet);
    m_bullet.setDevicePixelRatio(2);
    QPen pen;
    pen.setColor(m_color);
    pen.setWidth(10);
    paint->setPen(pen);
    paint->setBrush(m_color.lighter(110));
    paint->drawEllipse(QPoint(m_bullet.width()/2,
                              m_bullet.height()/2), 45, 45);
}

QPixmap Tag::getBullet() {
    return m_bullet.scaled(30, 30);
}

QString Tag::getName() {
    return m_tagName;
}

void Tag::setName(QString value) {
    m_tagName = value;
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

