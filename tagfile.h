#ifndef TAGFILE_H
#define TAGFILE_H

#include <QColor>
#include <QString>
#include <QList>
#include <QIcon>
#include <QAbstractListModel>
#include <QDebug>
#include <QMimeData>

#include <QPixmap>
#include <QPainter>

class TagFile : public QObject {
    /* Représente un fichier dans un Tag
     * On sait jamais si il faudra des membres
     * ou des méthodes en plus mieux vaux faire une classe direct */
      Q_OBJECT
    private:
        QString m_filePath;
        QString name;
        QIcon icon;
    public:
        explicit TagFile(QString filePath);
        QString getPath();
        QString getName();
        QIcon getIcon();

};

#endif // TAGFILE_H
