#include "tagfile.h"

TagFile::TagFile(QString filePath)
    : QObject() {
    m_filePath = filePath;
}

QString TagFile::getPath() {
    return m_filePath;
}

QMimeType TagFile::getMimeType() {
    QMimeDatabase db;
    QMimeType type = db.mimeTypeForFile(m_filePath);
    return type;
}
