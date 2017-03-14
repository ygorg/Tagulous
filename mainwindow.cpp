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

    tagListModel = new TagListModel(tagList, 0);

    listView = new QListView();
    listView->setModel(tagListModel);
    listView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    listView->setDragEnabled(true);
    listView->setAcceptDrops(true);
    listView->setDropIndicatorShown(true);
    listView->setAttribute(Qt::WA_MacShowFocusRect, false);

    listView2 = new QListView();
    listView2->setModel(tagListModel);
    listView2->setSelectionMode(QAbstractItemView::ExtendedSelection);
    listView2->setDragEnabled(true);
    listView2->setAcceptDrops(true);
    listView2->setDropIndicatorShown(true);
    listView2->setAttribute(Qt::WA_MacShowFocusRect, false);


    /* Some icones might be here : /System/Library/CoreServices/SystemAppearance.bundle/Contents/Resources */
    QAction *addAction = new QAction(QIcon::fromTheme("list-add"), tr("Add"), this);
    connect(addAction, SIGNAL(triggered(bool)),
            tagListModel, SLOT(requestedAddTag()));


    QAction *toggleSideBarAction = new QAction(QIcon::fromTheme("NSImageNameTouchBarSidebarTemplate"), tr("Show"), this);
    connect(toggleSideBarAction, SIGNAL(triggered(bool)),
            this, SLOT(toggleSideBar()));

    QAction *deleteAction = new QAction(tr("Delete"), this);
    connect(deleteAction, SIGNAL(triggered(bool)),
            this, SLOT(deleteElement()));

    QToolBar *toolbar_ = new QToolBar(this);
    setUnifiedTitleAndToolBarOnMac(true);

    toolbar_->setMovable(false);
    toolbar_->setFloatable(false);
    toolbar_->addAction(addAction);
    toolbar_->addAction(toggleSideBarAction);
    toolbar_->addAction(deleteAction);

    qDebug() << QIcon::hasThemeIcon("list-add") << QIcon::themeName() << QIcon::themeSearchPaths();

    this->addToolBar(toolbar_);


    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(listView2);
    layout->addWidget(listView);

    setCentralWidget(new QWidget);
    centralWidget()->setLayout(layout);

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
