#ifndef TAG_H
#define TAG_H

#include <QList>
#include <QColor>
#include <QString>
#include <QPixmap>
#include <QPen>
#include <QPainter>

#include "tagfile.h"

class Tag : public QList<TagFile *> {
/* Un tag c'est avant tout une liste de fichier
 * avec une couleur (pour le cercle mais c'est a voir)*/
private:
    QString m_tagName;
    QColor m_color;
    QPixmap m_bullet;
public:
    explicit Tag(QString tagName);
    void setBulletColor(QColor color);
    QPixmap getBullet();
    QColor getColor();
    QString getName();
    void setName(QString value);

    void insert(int i, TagFile *value);
    void removeAt(int i);
};

#endif // TAG_H
