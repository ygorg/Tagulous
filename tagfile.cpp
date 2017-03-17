#include "tagfile.h"

TagFile::TagFile(QString filePath)
    : QObject() {
    m_filePath = filePath;
    name = filePath.section(',', -1, -1);
    icon = QIcon(":icons/fileicon.png");
    TagFile::newTagFile(this);
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
    TagFile::deleteTagFile(this);
    delete parentTags;
}


/******
 * Static functions
 *
 * We keep track of created TagFile so each instance is unique
 *
 ******/

QSet<TagFile *> *TagFile::instances = new QSet<TagFile *>;

void TagFile::newTagFile(TagFile *file) {
    instances->insert(file);
}

void TagFile::deleteTagFile(TagFile *file) {
    instances->remove(file);
}

TagFile *TagFile::find(QString path) {
    for (TagFile *file : *instances) {
        if (file->getPath() == path) {
            return file;
        }
    }
    return new TagFile(path);
}

