#include "filelistwidget.h"

FileListWidget::FileListWidget(QWidget *parent)
    : QWidget(parent) {

    /* Initialize the widgets and variables */
    _searchBox = new QLineEdit();
    _searchBox->setPlaceholderText(tr("Search"));
    _searchBox->setAttribute(Qt::WA_MacShowFocusRect, false);
    _searchBox->setObjectName("searchLineEdit");

    _view = new QListViewDrop;
    _view->setSelectionMode(QAbstractItemView::ExtendedSelection);
    _view->setAcceptDrops(true);
    _view->setDropIndicatorShown(true);
    _view->setAttribute(Qt::WA_MacShowFocusRect, false);
    connect(_view, SIGNAL(doubleClicked(QModelIndex)),
            this, SLOT(requestOpenFile(QModelIndex)));

    //_proxyModel = new QSortFilterProxyModelFixed();
    //_proxyModel->setFilterRole(Qt::DisplayRole);
    //_proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    //connect(_searchBox, SIGNAL(textChanged(QString)),
    //        _proxyModel, SLOT(setFilterRegExp(QString)));
    _proxyModel = new QIdentityProxyModel;
    _view->setModel(_proxyModel);

    /* Defining the layout */
    _layout = new QVBoxLayout;
    _layout->setSpacing(0);
    _layout->setMargin(0);
    _layout->addWidget(_searchBox);
    _layout->addWidget(_view);
    this->setLayout(_layout);

}

void FileListWidget::setModel(FileListModel *model) {
    _model = model;
    connect(_view, SIGNAL(requestAddFiles(QList<QUrl>)),
            _model, SLOT(addFiles(QList<QUrl>)));
    _proxyModel->setSourceModel(_model);
}

void FileListWidget::connectActions(QMap<QString, QAction *> *actions) {
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
    connect(actions->value("previous"), SIGNAL(triggered(bool)),
            this, SLOT(previous()));

    connect(actions->value("open"), SIGNAL(triggered(bool)),
            this, SLOT(requestOpenFile()));

    connect(actions->value("openInExplorer"), SIGNAL(triggered(bool)),
            this, SLOT(requestOpenFileInFinder()));

}

void FileListWidget::addElement() {
    /* QFileDialog does not allow to select files and directories
     * A fix would be to reimplement QFileDialog ...
     * Prefer drag'n'drop over addActions
     */

    QFileDialog *dialog = new QFileDialog();
    dialog->setDirectory(QDir::homePath());
    QStringList fileNames;

    if (dialog->exec())
        fileNames = dialog->selectedFiles();
    delete dialog;

    _model->addFiles(fileNames);
}

void FileListWidget::deleteElement() {
    // Removing element from last to first as we operate on a list
    QModelIndexList indexes = _view->selectionModel()->selectedRows();
    std::sort(indexes.begin(), indexes.end());
    QModelIndexList::reverse_iterator it;

    for(it = indexes.rbegin(); it != indexes.rend(); ++it) {
        _view->model()->removeRow(it->row(), it->parent());
    }
}
void FileListWidget::copyElement() {
    qDebug() << "Copy on tags to be implemented";
}
void FileListWidget::pasteElement() {
    qDebug() << "Paste on tags to be implemented";
}

void FileListWidget::activateFind() {
    // If ctrl+f if pressed setting focus in the search field
    _searchBox->setFocus();
}


void FileListWidget::previous() {
    // The user want to go back to the tag view
    delete _model;
    emit viewTagList();
}

void openFile(QUrl url) {
    QDesktopServices::openUrl(url);
}

void openFile(QString path) {
    if (!path.startsWith("file://")) {
        path  = "file://" + path;
    }
    openFile(QUrl(path));
}

void FileListWidget::requestOpenFile(QModelIndex index) {
    QString path = index.data(FileListModel::MyRoles::PathRole).toString();
    openFile(path);
}

bool confirmMultipleOpenings(int len) {
    // If trying to open more that thresold file asking for confirmation
    static int thresold = 4;
    if (len > thresold) {
        QMessageBox msgBox;
        msgBox.setText(QString("You are about to open %1 file%2.").arg(len).arg(len > 1 ? "s" : ""));
        msgBox.setStandardButtons(QMessageBox::Cancel | QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Cancel);
        return msgBox.exec() == QMessageBox::Ok ? true : false;
    }
    return true;
}

void FileListWidget::requestOpenFile() {
    QModelIndexList indexes = _view->selectionModel()->selectedRows();
    if (!confirmMultipleOpenings(indexes.length())) {
        return;
    }
    for (QModelIndex index : indexes) {
        requestOpenFile(index);
    }
}

void FileListWidget::requestOpenFileInFinder() {
    QModelIndexList indexes = _view->selectionModel()->selectedRows();
    if (!confirmMultipleOpenings(indexes.length())) {
        return;
    }
    for (QModelIndex index : indexes) {
        QString path = index.data(FileListModel::MyRoles::PathRole).toString();
        if (!QDir(path).exists()) {
            path = path.section('/', 0, -2);
        }
        openFile(path);
    }
}

FileListWidget::~FileListWidget() {
    delete _layout;
    delete _view;
    delete _searchBox;
    delete _proxyModel;
}
