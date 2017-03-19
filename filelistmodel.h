#ifndef FILELISTMODEL_H
#define FILELISTMODEL_H

#include <QString>
#include <QList>
#include <QIcon>
#include <QAbstractListModel>

#import "tag.h"
#import "tagfile.h"

class FileListModel : public QAbstractListModel {
    // A model representing tagged files
    // This is where all the magic happens
    Q_OBJECT
private:
    QList<Tag*> *_tagList;
public:
    enum MyRoles {
        PathRole = Qt::UserRole + 1 // This role is used to get the path of a file
    };
    FileListModel(QList<Tag*> *, QObject *parent=0);
    FileListModel(Tag *, QObject *parent=0); // convenience constructor

    TagFile *getFile(int) const;


    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    bool removeRows(int row, int count, const QModelIndex &parent) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QHash<int,QByteArray>roleNames() const override;

public slots:
    void addFiles(QList<QUrl>);
    void addFiles(QStringList);
};

#endif // FILELISTMODEL_H
