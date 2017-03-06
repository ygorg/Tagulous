#include "tagfile.h"

TagFile::TagFile(QString filePath)
    : QObject() {
    m_filePath = filePath;
}

QString TagFile::getPath() {
    return m_filePath;
}
