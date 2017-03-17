#include "tagfile.h"

TagFile::TagFile(QString filePath)
    : QObject() {
    m_filePath = filePath;
    name = "";
    icon = QIcon();
}

QString TagFile::getPath() {
    return m_filePath;
}

QMimeType TagFile::getMimeType() {
    QMimeDatabase db;
    QMimeType type = db.mimeTypeForFile(m_filePath);
    return type;
}

QString TagFile::getName() {
    return "name";
}

QIcon TagFile::getIcon() {
    return icon;
}

QList<Tag *> *TagFile::getTags() {
    return parentTags;
}


/******
 * Handshake with Tag so we can know for
 * every file which tags contains the file
 ******/

void TagFile::addParentTag(Tag *tag) const {
    parentTags->append(tag);
}

void TagFile::removeParentTag(Tag *tag) {
    parentTags->removeOne(tag);
}

TagFile::~TagFile() {
    delete parentTags;
}
