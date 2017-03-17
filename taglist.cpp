#include "taglist.h"

TagList::TagList()
    : QList<Tag *>()
{}

void TagList::fromXML(QXmlStreamReader *reader) {

    Tag *currentTag;
    TagFile *currentFile;
    bool inFile = false;

    while (!reader->atEnd()) {
        reader->readNext();
        if (reader->isWhitespace()) {
            continue;
        }

        switch (reader->tokenType()) {
        case QXmlStreamReader::StartElement:
            if (reader->name() == "tag") {

                QString name = reader->attributes().value("name").toString();
                QStringList colorValues = reader->attributes().value("color")
                        .toString().split(" ");
                QColor color(colorValues[0].toInt(), colorValues[1].toInt(),
                        colorValues[2].toInt(), colorValues[3].toInt());

                currentTag = new Tag(name);
                currentTag->setBulletColor(color);

            } else if (reader->name() == "file") {
                inFile = true;
            }
            break;
        case QXmlStreamReader::EndElement:
            if (reader->name() == "tag") {
                this->append(currentTag);
                currentTag = nullptr;

            } else if (reader->name() == "file") {
                currentTag->append(currentFile);
                currentFile = nullptr;
                inFile = false;
            }
            break;
        case QXmlStreamReader::Characters:
            if (inFile) {
                currentFile = TagFile::find(reader->text().toString());
            }
            break;
        default:
            break;
        }
    }
}

void TagList::toXML(QXmlStreamWriter *writer) {

    writer->setAutoFormatting(true);

    writer->writeStartDocument();

    writer->writeStartElement("taglist");
    for (Tag *tag : *this) {
        QColor color = tag->getColor();
        QString colorStr("%1 %2 %3 %4");
        colorStr = colorStr.arg(color.red()).arg(color.green())
                           .arg(color.blue()).arg(color.alpha());

        writer->writeStartElement("tag");
        writer->writeAttribute("name", tag->getName());
        writer->writeAttribute("color", colorStr);

        for (TagFile *file : *tag) {
            writer->writeStartElement("file");
            writer->writeCharacters(file->getPath());
            writer->writeEndElement();
        }

        writer->writeEndElement();
    }
    writer->writeEndElement();

    writer->writeEndDocument();
}

void TagList::init() {
    Tag *tag = new Tag("Tag1");
    tag->setBulletColor(QColor(252, 61, 57));
    this->append(tag);

    tag = new Tag("Tag2");
    tag->setBulletColor(QColor(104, 216, 69));
    this->append(tag);

    tag = new Tag("Tag3");
    tag->setBulletColor(QColor(42, 174, 245));
    this->append(tag);
}
