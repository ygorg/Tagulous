#ifndef TAGFILE_H
#define TAGFILE_H

#include <QObject>
#include <QString>
#include <QMimeDatabase>
#include <QMimeType>

class TagFile : public QObject {
    /* Représente un fichier dans un Tag
     * On sait jamais si il faudra des membres
     * ou des méthodes en plus mieux vaux faire une classe direct */
      Q_OBJECT
    private:
        QString m_filePath;
    public:
        explicit TagFile(QString filePath);
        QString getPath();
        QMimeType getMimeType();

};

#endif // TAGFILE_H
