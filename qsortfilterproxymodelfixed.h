#ifndef QSORTFILTERPROXYMODELFIXED_H
#define QSORTFILTERPROXYMODELFIXED_H

#include <QSortFilterProxyModel>

class QSortFilterProxyModelFixed : public QSortFilterProxyModel {

    int rowCount(const QModelIndex &parent = QModelIndex()) const {
        int sourceRowCount = sourceModel()->rowCount(parent);
        int thisRowCount = QSortFilterProxyModel::rowCount(parent);
        if (thisRowCount > sourceRowCount) {
            return sourceRowCount;
        }
        return thisRowCount;
    }

};

#endif // QSORTFILTERPROXYMODELFIXED_H
