#include "filelistwidget.h"
#include <QDebug>

FileListWidget::FileListWidget(QMap<QString, QAction *> *actions,
                             QWidget *parent)
    : QWidget(parent) {

    /* Initialize the widgets and variables */
    _actions = actions;
    _layout = new QVBoxLayout;
    _fileView = new QListViewDrop;
    _searchBox = new QLineEdit();
    _searchBox->setPlaceholderText(tr("Search"));

    _fileView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    _fileView->setDragEnabled(true);
    _fileView->setAcceptDrops(true);
    _fileView->setDropIndicatorShown(true);
    _fileView->setAttribute(Qt::WA_MacShowFocusRect, false);
    _fileView->setEditTriggers(QAbstractItemView::SelectedClicked);

    /* Defining the layout */
    _layout->addWidget(_searchBox);
    _layout->addWidget(_fileView);
    this->setLayout(_layout);
}

void FileListWidget::setModel(FileListModel *model) {
    _fileListModel = model;
    _fileView->setModel(_fileListModel);
}

FileListModel *FileListWidget::getModel() {
    return _fileListModel;
}



void FileListWidget::connectActions() {

    /* Connect the wanted action to the wanted slot */
    /* Tell if you want to action to be shown in the toolbar
     * and/or the menu */

    connect(_actions->value("add"), SIGNAL(triggered(bool)),
            this, SLOT(requestedAddFiles()));
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


    connect(_actions->value("previous"), SIGNAL(triggered(bool)),
            this, SLOT(previous()));
    emit toolBarAction("previous");


    connect(_actions->value("open"), SIGNAL(triggered(bool)),
            this, SLOT(openFile()));
    emit toolBarAction("open");

    connect(_actions->value("openInExplorer"), SIGNAL(triggered(bool)),
            this, SLOT(openFileInFinder()));
    emit toolBarAction("openInExplorer");

}

void FileListWidget::requestedAddFiles() {
    qDebug() << "Add files to be implemented";
}

void FileListWidget::deleteElement() {
    /* Removing element from last to first as we operate on a list
     * removing the first element moves all the other...
     */

    QModelIndexList indexes = _fileView->selectionModel()->selectedRows();
    std::sort(indexes.begin(), indexes.end());
    QModelIndexList::reverse_iterator it;

    for(it = indexes.rbegin(); it != indexes.rend(); ++it) {
        //delete tagList->at(index.row());
        _fileListModel->removeRow(it->row(), it->parent());
    }
}
void FileListWidget::copyElement() {
    qDebug() << "Copy on tags to be implemented";
}
void FileListWidget::pasteElement() {
    qDebug() << "Paste on tags to be implemented";
}

void FileListWidget::activateFind() {
    _searchBox->setFocus();
}


void FileListWidget::previous() {
    delete _fileListModel;
    emit viewTagList();
}


void FileListWidget::openFile() {
    qDebug() << "Multi selection to be implemented";
    //QModelIndexList indexes
}

void FileListWidget::openFileInFinder() {
    qDebug() << "Openning files in finder to be implemented";
    //QModelIndexList indexes
}
