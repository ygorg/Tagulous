#include "taglistwidget.h"

TagListWidget::TagListWidget(TagListModel *tagListModel,
                             QMap<QString, QAction *> *actions,
                             QWidget *parent)
    : QWidget(parent) {

    /* Initialize the widgets and variables */
    _actions = actions;
    _tagListModel = tagListModel;
    _layout = new QVBoxLayout;
    _tagView = new QListView;
    _searchBox = new QLineEdit();
    _searchBox->setPlaceholderText(tr("Search"));
    _searchBox->setAttribute(Qt::WA_MacShowFocusRect, false);

    _proxyModel = new QSortFilterProxyModelFixed();
    _proxyModel->setFilterRole(Qt::DisplayRole);
    _proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    _proxyModel->setSourceModel(_tagListModel);

    connect(_searchBox, SIGNAL(textChanged(QString)),
            _proxyModel, SLOT(setFilterRegExp(QString)));

    _tagView->setModel(_proxyModel);
    _tagView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    _tagView->setDragEnabled(true);
    _tagView->setAcceptDrops(true);
    _tagView->setDropIndicatorShown(true);
    _tagView->setAttribute(Qt::WA_MacShowFocusRect, false);
    _tagView->setEditTriggers(QAbstractItemView::SelectedClicked);
    connect(_tagView, SIGNAL(doubleClicked(QModelIndex)),
            this, SLOT(doubleClicked(QModelIndex)));

    /* Defining the layout */
    _layout->addWidget(_searchBox);
    _layout->addWidget(_tagView);
    this->setLayout(_layout);
}


void TagListWidget::connectActions() {

    /* Connect the wanted action to the wanted slot */
    /* Tell if you want to action to be shown in the toolbar
     * and/or the menu */

    connect(_actions->value("add"), SIGNAL(triggered(bool)),
            this, SLOT(addElement()));
    emit toolBarAction("add");


    connect(_actions->value("copy"), SIGNAL(triggered(bool)),
            this, SLOT(copyElement()));


    connect(_actions->value("paste"), SIGNAL(triggered(bool)),
            this, SLOT(pasteElement()));


    connect(_actions->value("remove"), SIGNAL(triggered(bool)),
            this, SLOT(deleteElement()));
    emit toolBarAction("remove");

    connect(_actions->value("find"), SIGNAL(triggered(bool)),
            this, SLOT(activateFind()));
    emit toolBarAction("find");


    connect(_actions->value("rename"), SIGNAL(triggered(bool)),
            this, SLOT(renameElement()));
    emit toolBarAction("rename");


    connect(_actions->value("filter"), SIGNAL(triggered(bool)),
            this, SLOT(filterTags()));
    emit toolBarAction("filter");

}

void TagListWidget::addElement() {
    _tagView->model()->insertRow(_tagView->model()->rowCount());
}

void TagListWidget::deleteElement() {
    /* Removing element from last to first as we operate on a list
     * removing the first element moves all the other...
     */
    QModelIndexList indexes = _tagView->selectionModel()->selectedRows();
    std::sort(indexes.begin(), indexes.end());
    QModelIndexList::reverse_iterator it;

    for(it = indexes.rbegin(); it != indexes.rend(); ++it) {
        _tagView->model()->removeRow(it->row(), it->parent());
    }
}

void TagListWidget::renameElement() {
    if (_tagView->selectionModel()->selectedRows().length() <= 0) {
        return;
    }
    /* Editing the first item if more than one is selected */
    _tagView->edit(_tagView->selectionModel()->selectedRows().at(0));
}

void TagListWidget::copyElement() {
    qDebug() << "Copy on tags to be implemented";
}
void TagListWidget::pasteElement() {
    qDebug() << "Paste on tags to be implemented";
}

void TagListWidget::activateFind() {    
    _searchBox->setFocus();
}

void TagListWidget::filterTags() {
    //TODO here add checkboxes in front of the tags
    qDebug() << "Multi selection to be implemented";
}

void TagListWidget::doubleClicked(QModelIndex index) {
    if (!index.isValid()) {
        return;
    }
    /* We want to change view so we SIGNAL it */
    emit viewFileList(index.row());
}

TagListWidget::~TagListWidget() {
    delete _layout;
    delete _tagView;
    delete _searchBox;
    delete _proxyModel;
}
