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
    // A TagFile is a file that is associated with a/some Tag
      Q_OBJECT
    private:
        // We keep track of every TagFile created
        static QSet<TagFile *> *instances;

        QList<Tag *> *_parentTags = new QList<Tag *>;
        QString _filePath;
        QString _name;
        QIcon _icon;

        // The constructor is private to prevent multiple TagFile
        // with the same path to exist
        explicit TagFile(QString filePath);

    public:
        static void newTagFile(TagFile *file);
        static void deleteTagFile(TagFile *file);
        static TagFile *find(QString path);
        static QSet<TagFile *> *getInstance();


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
