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

QString TagFile::getName() {
    return name;
}

QIcon TagFile::getIcon() {
    return icon;
}
