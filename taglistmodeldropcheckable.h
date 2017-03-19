#ifndef TAGLISTMODELDROPCHECKABLE_H
#define TAGLISTMODELDROPCHECKABLE_H

#include "taglistmodeldrop.h"

class TagListModelDropCheckable : public TagListModelDrop {
    // This model add support for selecting tags using checkboxes
private:
    bool filterIsOn = false;
    QHash<Tag *, int> *checkState = new QHash<Tag *, int>;

    int getCheckState(Tag *tag) const;
    void setCheckState(Tag *tag, int value);

public:
    TagListModelDropCheckable(TagList *, QObject *parent=0);
    ~TagListModelDropCheckable();

    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QVariant data(const QModelIndex &index,
                    int role) const override;
    bool setData(const QModelIndex &index,
                    const QVariant &value, int role) override;
    QModelIndexList *getChecked();

public slots:
    void toggleFilter(bool);
};

#endif // TAGLISTMODELDROPCHECKABLE_H
