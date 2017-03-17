#include "tag.h"

Tag::Tag(QString tagName)
                    : QList<TagFile *>() {
    _tagName = tagName;
    _bullet = QPixmap(100, 100);
}

void Tag::setBulletColor(QColor color) {
    this->_color = color;
    _bullet.fill(QColor(0, 0, 0, 0));

    QPainter *paint = new QPainter(&_bullet);
    _bullet.setDevicePixelRatio(2);
    QPen pen;
    pen.setColor(_color);
    pen.setWidth(10);
    paint->setPen(pen);
    paint->setBrush(_color.lighter(110));
    paint->drawEllipse(QPoint(_bullet.width()/2,
                              _bullet.height()/2), 45, 45);
}

QColor Tag::getColor() {
    return _color;
}

QPixmap Tag::getBullet() {
    return _bullet.scaled(30, 30);
}

QString Tag::getName() {
    return _tagName;
}

void Tag::setName(QString value) {
    _tagName = value;
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
