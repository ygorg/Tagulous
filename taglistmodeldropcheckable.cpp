#include "taglistmodeldropcheckable.h"

TagListModelDropCheckable::TagListModelDropCheckable(TagList *tagList, QObject *parent)
    : TagListModelDrop(tagList, parent)
{}

int TagListModelDropCheckable::getCheckState(Tag *tag) const {
    if (!checkState->contains(tag)) {
        checkState->insert(tag, Qt::Unchecked);
    }
    return checkState->value(tag);
}
void TagListModelDropCheckable::setCheckState(Tag *tag, int value) {
    checkState->insert(tag, value);
}

Qt::ItemFlags TagListModelDropCheckable::flags(const QModelIndex &index) const {
    if (filterIsOn)
        return TagListModelDrop::flags(index)
                | Qt::ItemIsUserCheckable;
    else
        return TagListModelDrop::flags(index);
}

QVariant TagListModelDropCheckable::data(const QModelIndex &index,
                            int role) const {
    //Qt::CheckState
    if (role != Qt::CheckStateRole) {
        return TagListModelDrop::data(index, role);
    }

    if (filterIsOn) {
        return getCheckState(_tags->at(index.row()));
    } else {
        return QVariant();
    }
}

bool TagListModelDropCheckable::setData(const QModelIndex &index,
                           const QVariant &value, int role) {
    if (role != Qt::CheckStateRole) {
        return TagListModelDrop::setData(index, value, role);
    }

    setCheckState(_tags->at(index.row()), value.toInt());
    emit dataChanged(index, index);
    return true;
}

QModelIndexList *TagListModelDropCheckable::getChecked() {
    QModelIndexList *checked = new QModelIndexList;

    for(int i = 0; i < rowCount(); i++) {
        if(getCheckState(_tags->at(i)) == Qt::Checked) {
            checked->append(index(i));
        }
    }
    return checked;
}

void TagListModelDropCheckable::toggleFilter(bool activated) {
    filterIsOn = activated;
    emit dataChanged(index(0), index(rowCount()));
}

TagListModelDropCheckable::~TagListModelDropCheckable() {
    delete checkState;
}
