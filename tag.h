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

#include "TagFile.h"

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
    QString getName();
    void setName(QString value);
};

#endif // TAG_H
