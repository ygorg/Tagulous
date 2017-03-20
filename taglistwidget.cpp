#include "taglistwidget.h"

TagListWidget::TagListWidget(QWidget *parent)
    : QWidget(parent) {

    /* Initialize the widgets and variables */
    _searchBox = new QLineEdit();
    _searchBox->setPlaceholderText(tr("Search"));
    _searchBox->setAttribute(Qt::WA_MacShowFocusRect, false);
    _searchBox->setObjectName("searchLineEdit");

    _view = new QListView;
    _view->setSelectionMode(QAbstractItemView::ExtendedSelection);
    _view->setAcceptDrops(true);
    _view->setDropIndicatorShown(true);
    _view->setAttribute(Qt::WA_MacShowFocusRect, false);
    _view->setEditTriggers(QAbstractItemView::SelectedClicked);
    connect(_view, SIGNAL(doubleClicked(QModelIndex)),
            this, SLOT(doubleClicked(QModelIndex)));

    //_proxyModel = new QSortFilterProxyModelFixed();
    //_proxyModel->setFilterRole(Qt::DisplayRole);
    //_proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    //connect(_searchBox, SIGNAL(textChanged(QString)),
    //        _proxyModel, SLOT(setFilterRegExp(QString)));
    _proxyModel = new QIdentityProxyModel();
    _view->setModel(_proxyModel);

    _filterValidateButton = new QPushButton();
    _filterValidateButton->setText(tr("Ok"));
    _filterValidateButton->hide();
    connect(_filterValidateButton, SIGNAL(clicked(bool)),
            this, SLOT(requestedFilter()));

    /* Defining the layout */
    _layout = new QVBoxLayout;
    _layout->setSpacing(0);
    _layout->setMargin(0);
    _layout->addWidget(_searchBox);
    _layout->addWidget(_view);
    _layout->addWidget(_filterValidateButton);
    this->setLayout(_layout);
}

void TagListWidget::setModel(TagListModelDropCheckable *model) {
    _model = model;
    _proxyModel->setSourceModel(_model);
}

void TagListWidget::connectActions(QMap<QString, QAction *> *actions) {
    // General actions
    connect(actions->value("add"), SIGNAL(triggered(bool)),
            this, SLOT(addElement()));

    connect(actions->value("copy"), SIGNAL(triggered(bool)),
            this, SLOT(copyElement()));

    connect(actions->value("paste"), SIGNAL(triggered(bool)),
            this, SLOT(pasteElement()));

    connect(actions->value("remove"), SIGNAL(triggered(bool)),
            this, SLOT(deleteElement()));

    connect(actions->value("find"), SIGNAL(triggered(bool)),
            this, SLOT(activateFind()));

    // Specific actions
    connect(actions->value("rename"), SIGNAL(triggered(bool)),
            this, SLOT(renameElement()));

    connect(actions->value("filter"), SIGNAL(triggered(bool)),
            this, SLOT(filterTags()));
}

void TagListWidget::addElement() {
    // Add a new empty tag to the end of the list
    QAbstractItemModel *model = _view->model();
    model->insertRow(model->rowCount());
    _view->edit(model->index(model->rowCount() - 1, 0));
    _view->scrollTo(model->index(model->rowCount() - 1, 0));
}

void TagListWidget::deleteElement() {
    // Removing element from last to first as we operate on a list
    QModelIndexList indexes = _view->selectionModel()->selectedRows();
    std::sort(indexes.begin(), indexes.end());
    QModelIndexList::reverse_iterator it;

    for(it = indexes.rbegin(); it != indexes.rend(); ++it) {
        _view->model()->removeRow(it->row(), it->parent());
    }
}

void TagListWidget::copyElement() {
    qDebug() << "Copy on tags to be implemented";
}
void TagListWidget::pasteElement() {
    qDebug() << "Paste on tags to be implemented";
}

void TagListWidget::activateFind() {
    // If ctrl+f if pressed setting focus in the search field
    _searchBox->setFocus();
}

void TagListWidget::renameElement() {
    // Triggers the editting of a selected element
    QModelIndexList selectedIndexes = _view->selectionModel()->selectedRows();
    if (selectedIndexes.length() <= 0) {
        return;
    }
    std::sort(selectedIndexes.begin(), selectedIndexes.end());
    /* Editing the first item if more than one is selected */
    _view->edit(selectedIndexes.at(0));
}

void TagListWidget::filterTags() {
    // Here the user wants to see the files of multiple tags
    // checkboxes are shown in front of the tags
    // a "Ok" button appears to validate the selection
    filterIsOn = !filterIsOn;
    _model->toggleFilter(filterIsOn);
    if (filterIsOn) {
        _filterValidateButton->show();
    } else {
        _filterValidateButton->hide();
    }
}

void TagListWidget::requestedFilter() {
    // The user activated the filter mode and clicked on "Ok"
    // we show the files the user asked for
    QModelIndexList *indexes = _model->getChecked();
    if (indexes->length() == 0) {
        return;
    }
    emit viewFileList(indexes);
}

void TagListWidget::doubleClicked(QModelIndex index) {
    // The user double clicked on an item
    // we show the files associated with the tag double clicked
    if (!index.isValid()) {
        return;
    }
    /* We want to change view so we SIGNAL it */
    QModelIndexList *indexes = new QModelIndexList();
    indexes->append(index);
    emit viewFileList(indexes);
}

TagListWidget::~TagListWidget() {
    delete _layout;
    delete _view;
    delete _searchBox;
    delete _proxyModel;
}
