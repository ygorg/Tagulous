#ifndef TAGFILE_H
#define TAGFILE_H

#include <QObject>
#include <QString>
#include <QIcon>
#include <QMimeDatabase>
#include <QMimeType>
#include <QSet>


class Tag;

class TagFile : public QObject {
    /* Représente un fichier dans un Tag
     * On sait jamais si il faudra des membres
     * ou des méthodes en plus mieux vaux faire une classe direct */
      Q_OBJECT
    private:
        static QSet<TagFile *> *instances;

        QList<Tag *> *parentTags = new QList<Tag *>;
        QString m_filePath;
        QString name;
        QIcon icon;

        explicit TagFile(QString filePath);

    public:
        static void newTagFile(TagFile *file);
        static void deleteTagFile(TagFile *file);
        static TagFile *find(QString path);

        QString getPath();
        QMimeType getMimeType();
        QString getName();
        QIcon getIcon();

        QList<Tag *> *getTags();
        void addParentTag(Tag *tag) const;
        void removeParentTag(Tag *tag);
        ~TagFile();

};

#endif // TAGFILE_H
