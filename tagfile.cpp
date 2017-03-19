#include "tagfile.h"

TagFile::TagFile(QString filePath)
    : QObject() {
    _filePath = filePath;
    _name = filePath.split("/", QString::SkipEmptyParts).last();
    _icon = QIcon(":icons/file");
    TagFile::newTagFile(this);
}

QString TagFile::getPath() {
    return _filePath;
}

QMimeType TagFile::getMimeType() {
    QMimeDatabase db;
    QMimeType type = db.mimeTypeForFile(_filePath);
    return type;
}

QString TagFile::getName() {
    return _name;
}

QIcon TagFile::getIcon() {
    return _icon;
}

QList<Tag *> *TagFile::getTags() {
    return _parentTags;
}


/******
 * Handshake with Tag so we can know for
 * every file which tags contains the file
 ******/

void TagFile::addParentTag(Tag *tag) const {
    _parentTags->append(tag);
}

void TagFile::removeParentTag(Tag *tag) {
    _parentTags->removeOne(tag);
}

TagFile::~TagFile() {
    TagFile::deleteTagFile(this);
    delete _parentTags;
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
    // Searching for an existing file
    for (TagFile *file : *instances) {
        if (file->getPath() == path) {
            return file;
        }
    }
    return new TagFile(path);
}

QSet<TagFile *> *TagFile::getInstance() {
    return instances;
}

