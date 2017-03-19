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
    QString _tagName;
    QColor _color;
    QPixmap _bullet;
public:
    explicit Tag(QString tagName);
    void setBulletColor(QColor color);
    QPixmap getBullet();
    QColor getColor();
    QString getName();
    void setName(QString value);

    void append(const QList<TagFile *> &t);
    void append(TagFile * const &t);
    void insert(int i, TagFile *value);
    void removeAt(int i);
};

#endif // TAG_H
