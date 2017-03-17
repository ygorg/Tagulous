#include "tag.h"

Tag::Tag(QString tagName)
                    : QList<TagFile *>() {
    m_tagName = tagName;
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

QColor Tag::getColor() {
    return m_color;
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

/*****
 * Handshake with TagFile
 *****/

void Tag::insert(int i, TagFile *value) {
    value->addParentTag(this);
    QList::insert(i, value);
}
void Tag::removeAt(int i) {
    at(i)->removeParentTag(this);
    QList::removeAt(i);
}

//TODO faire une classe qui hérite de QList<Tag *>
// et qui représente les Tags
// pour avoir un slot requestedAddFiles(int row, QList<TagFile *>)
