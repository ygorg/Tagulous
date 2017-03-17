#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{

    tagList = new TagList;

    QFile file(path + "/" + fileName);
    QString data;
    if (file.open(QIODevice::ReadOnly))
    {
        QXmlStreamReader *reader = new QXmlStreamReader(&file);
        tagList->fromXML(reader);
        file.close();
        qDebug() << path + "/" + fileName;
    } else {
        tagList->init();
        qDebug() << "Unable to load the data.";
    }

    tagListModel = new TagListModelDrop(tagList);
    QList<Tag *> *lst = new QList<Tag *>();
    lst->append(tagList->at(1));
    //lst->append(tagList->at(3));
    fileListModel = new FileListModel(lst);


    listView = new QListView();
    listView->setModel(tagListModel);
    listView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    listView->setDragEnabled(true);
    listView->setAcceptDrops(true);
    listView->setDropIndicatorShown(true);
    listView->setAttribute(Qt::WA_MacShowFocusRect, false);
    listView->setEditTriggers(QAbstractItemView::SelectedClicked);
    connect(listView, SIGNAL(doubleClicked(QModelIndex)),
            this, SLOT(doubleClicked()));

    listView2 = new QListView();
    listView2->setModel(fileListModel);
    listView2->setSelectionMode(QAbstractItemView::ExtendedSelection);
    listView2->setDragEnabled(true);
    listView2->setAcceptDrops(true);
    listView2->setDropIndicatorShown(true);
    listView2->setAttribute(Qt::WA_MacShowFocusRect, false);

    qDebug() << QIcon::hasThemeIcon("list-add") << QIcon::themeName() << QIcon::themeSearchPaths();



    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(listView2);
    layout->addWidget(listView);

    createActions();

    setCentralWidget(new QWidget);
    centralWidget()->setLayout(layout);

}

void MainWindow::createActions() {
    /* Some icones might be here : /System/Library/CoreServices/SystemAppearance.bundle/Contents/Resources */
    QAction *addAction = new QAction(QIcon::fromTheme("list-add"), tr("Add"), this);
    addAction->setShortcut(QKeySequence::New);
    connect(addAction, SIGNAL(triggered(bool)),
            tagListModel, SLOT(requestedAddTag()));

    QAction *toggleSideBarAction = new QAction(QIcon::fromTheme("NSImageNameTouchBarSidebarTemplate"), tr("Show"), this);
    connect(toggleSideBarAction, SIGNAL(triggered(bool)),
            this, SLOT(toggleSideBar()));

    QAction *copyAction = new QAction(tr("Copy"), this);
    copyAction->setShortcut(QKeySequence::Copy);
    connect(copyAction, SIGNAL(triggered(bool)),
            this, SLOT(copyElement()));

    QAction *pasteAction = new QAction(tr("Paste"), this);
    pasteAction->setShortcut(QKeySequence::Paste);
    connect(pasteAction, SIGNAL(triggered(bool)),
            this, SLOT(pasteElement()));

    QAction *renameAction = new QAction(tr("Rename"), this);
    connect(renameAction, SIGNAL(triggered(bool)),
            this, SLOT(renameElement()));

    QAction *deleteAction = new QAction(tr("Delete"), this);
#ifdef Q_OS_MAC
    deleteAction->setShortcut(QKeySequence(Qt::Key_Backspace));
#else
    deleteAction->setShortcut(QKeySequence::Delete);
#endif /* Q_OS_MAC */

    connect(deleteAction, SIGNAL(triggered(bool)),
            this, SLOT(deleteElement()));

    QAction *selectTagsAction = new QAction(tr("Filter"), this);
    connect(selectTagsAction, SIGNAL(triggered(bool)),
            this, SLOT(selectTags()));


    QMenu *menu = new QMenu(tr("File"));
    menu->addAction(addAction);
    menu->addAction(toggleSideBarAction);
    menu->addAction(deleteAction);
    menu->addAction(renameAction);
    menu->addAction(copyAction);
    menu->addAction(pasteAction);

    QMenuBar *menuBar = new QMenuBar(0);
    menuBar->addMenu(menu);


    QToolBar *toolbar_ = new QToolBar(this);
    setUnifiedTitleAndToolBarOnMac(true);

    toolbar_->setMovable(false);
    toolbar_->setFloatable(false);
    toolbar_->addAction(addAction);
    toolbar_->addAction(toggleSideBarAction);
    toolbar_->addAction(deleteAction);
    toolbar_->addAction(renameAction);
    this->addToolBar(toolbar_);

}

void MainWindow::toggleSideBar() {
    sideBarIsShown = !sideBarIsShown;
    if (sideBarIsShown) {
        listView2->show();
    } else {
        listView2->hide();
    }
}

void MainWindow::deleteElement() {

    for (QModelIndex index : listView->selectionModel()->selectedRows()) {
        tagListModel->removeRow(index.row(), index.parent());
    }
}

void MainWindow::renameElement() {
    if (listView->selectionModel()->selectedRows().length() <= 0) {
        return;
    }
    listView->edit(listView->selectionModel()->selectedRows().at(0));
}

void MainWindow::copyElement() {}
void MainWindow::pasteElement() {}

void MainWindow::selectTags() {
    //TODO here add checkboxes in front of the tags
}

void MainWindow::doubleCLicked(QModelIndex index) {

    /*QList<Tag *> fileList = new QList<Tag *>();
    fileList.append(tagList->at(index.row()));

    fileListModel = new FileListModel(fileList);
    listView2->setModel(fileListModel);

    listView->hide();
    listView2->show();
    QToolBar *toolbar = new QToolBar();
    QAction *previousAction = new QAction(tr("Back"), this);
    connect(previousAction, SIGNAL(triggered(bool)),
            this, SLOT(goBack()));

    toolbar->addAction(previousAction);*/
}

MainWindow::~MainWindow() {

    QDir d;
    d.mkpath(path);

    QFile file(path + "/" + fileName);
    if (file.open(QIODevice::WriteOnly))
    {
        QXmlStreamWriter *writer = new QXmlStreamWriter(&file);
        tagList->toXML(writer);
        file.close();
        qDebug() << path + "/" + fileName;
    } else {
        qDebug() << "Unable to save the data.";
    }
}
