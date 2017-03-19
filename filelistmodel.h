#ifndef FILELISTMODEL_H
#define FILELISTMODEL_H

#include <QString>
#include <QList>
#include <QIcon>
#include <QAbstractListModel>

#import "tag.h"
#import "tagfile.h"

class FileListModel : public QAbstractListModel {
    Q_OBJECT
private:
    QList<Tag*> *_tagList;
public:
    enum MyRoles {
        PathRole = Qt::UserRole + 1,   /**< This role holds the object itself. */
    };
    FileListModel(QList<Tag*> *list, QObject *parent=0);
    FileListModel(Tag *tag, QObject *parent=0);
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
