#ifndef TAGLIST_H
#define TAGLIST_H

#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QList>
#include <QColor>

#include "tag.h"


class TagList : public QList<Tag *>
{

public:
    TagList();

    void fromXML(QXmlStreamReader *reader);
    void toXML(QXmlStreamWriter *writer);

    /* For test purpose */
    void init(); /* Initialises the model with false values */
};

#endif // TAGLIST_H
