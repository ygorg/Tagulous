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
    return name;
}

QIcon TagFile::getIcon() {
    return icon;
}
