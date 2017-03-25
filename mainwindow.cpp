#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{

    qDebug() << "BUG QSortFilterProxyModel::rowCount() is bugged so subclassing QAbstractProxyModel is needed...\n"
                "FIX QFileDialog doesn't allow files ann dirs to be selected at the same time...";

    createActions();

    _tagList = loadPersistance();

    _tagListModel = new TagListModelDropCheckable(_tagList);


    // Creating the main view

    // _tagListWidget displays the tags
    _tagListWidget = new TagListWidget;
    _tagListWidget->setModel(_tagListModel);
    connect(_tagListWidget, SIGNAL(viewFileList(QModelIndexList *)),
            this, SLOT(showFileList(QModelIndexList *)));

    // _fileListWidget displays tagged files
    _fileListWidget = new FileListWidget;
    connect(_fileListWidget, SIGNAL(viewTagList()),
            this, SLOT(showTagList()));

    _stackedWidget->addWidget(_tagListWidget);
    _stackedWidget->addWidget(_fileListWidget);
    setCentralWidget(_stackedWidget);

    // When opening the app the tags are shown
    showTagList();

}

void MainWindow::createActions() {
    // Creating all actions used across the app
    // Storing the actions in a HasMap for convenience

    // General Actions (not specific)
    QAction *addAction = new QAction(QIcon(":icons/add@2x"), tr("Add"), this);
    addAction->setShortcut(QKeySequence::New);
    _actions->insert("add", addAction);

    QAction *copyAction = new QAction(tr("Copy"), this);
    copyAction->setShortcut(QKeySequence::Copy);
    _actions->insert("copy", copyAction);


    QAction *pasteAction = new QAction(tr("Paste"), this);
    pasteAction->setShortcut(QKeySequence::Paste);
    _actions->insert("paste", pasteAction);


    QAction *removeAction = new QAction(QIcon(":icons/remove@2x"), tr("Remove"), this);
#ifdef Q_OS_MAC
    removeAction->setShortcut(QKeySequence(Qt::Key_Backspace));
#else
    removeAction->setShortcut(QKeySequence::Delete);
#endif /* Q_OS_MAC */
    _actions->insert("remove", removeAction);

    QAction *findAction = new QAction(QIcon(":icons/search@2x"), tr("Search"), this);
    findAction->setShortcut(QKeySequence::Find);
    _actions->insert("find", findAction);


    // TagListWidget specific actions
    QAction *renameAction = new QAction(tr("Rename"), this);
    _actions->insert("rename", renameAction);

    QAction *filterAction = new QAction(tr("Filter"), this);
    _actions->insert("filter", filterAction);


    // FileListWidget specific actions
    QAction *previousAction = new QAction(tr("Previous"), this);
    previousAction->setShortcut(QKeySequence::Back);
    _actions->insert("previous", previousAction);

    QAction *openInExplorerAction = new QAction(tr("Open in Finder"), this);
    _actions->insert("openInExplorer", openInExplorerAction);

    QAction *openAction = new QAction(tr("Open"), this);
    openAction->setShortcut(QKeySequence::Open);
    _actions->insert("open", openAction);


    //Initializing toolbar
    setUnifiedTitleAndToolBarOnMac(true);
    _toolbar->setMovable(false);
    _toolbar->setFloatable(false);
    _toolbar->setIconSize(QSize(15,15));

    //Adding general actions to the toolbar
    _toolbar->addAction(addAction);
    _toolbar->addAction(removeAction);
    _toolbar->addAction(findAction);
    this->addToolBar(_toolbar);


    //Initializing menu

#ifdef Q_OS_MAC
    _menuBar = new QMenuBar(0);
#else
    _menuBar = menuBar();
#endif /* Q_OS_MAC */

    //Adding general actions to the menu
    _menu->addAction(addAction);
    _menu->addAction(copyAction);
    _menu->addAction(pasteAction);
    _menu->addAction(removeAction);
    _menu->addAction(findAction);
    _menuBar->addMenu(_menu);

}

TagList *MainWindow::loadPersistance() {
    // Load data if available
    TagList *tagList = new TagList;

    QFile file(_path + "/" + _fileName);
    QString data;
    if (file.open(QIODevice::ReadOnly))
    {
        QXmlStreamReader *reader = new QXmlStreamReader(&file);
        tagList->fromXML(reader);
        file.close();
    } else {
        tagList->init(); //Load mockup data
        qDebug() << "Unable to load the data.";
    }

    return tagList;
}

void MainWindow::savePersistance(TagList *tagList) {
    // Save data
    QDir d;
    d.mkpath(_path);

    QFile file(_path + "/" + _fileName);
    if (file.open(QIODevice::WriteOnly))
    {
        QXmlStreamWriter *writer = new QXmlStreamWriter(&file);
        tagList->toXML(writer);
        file.close();
        delete writer;
    } else {
        qDebug() << "Unable to save the data.";
    }
}

void MainWindow::hideWidget() {

    // Disconnecting all actions
    QMapIterator<QString, QAction *> i(*_actions);
    while (i.hasNext()) {
        i.next();
        disconnect(i.value(), SIGNAL(triggered()), 0, 0);
    }

    /* When changing between tags and files
     *  - removing toolbar actions that are not general
     *  - removing menu actions that are not general
     */

    _toolbar->removeAction(getAction("previous"));
    _toolbar->removeAction(getAction("openInExplorer"));
    _toolbar->removeAction(getAction("open"));
    _toolbar->removeAction(getAction("rename"));
    _toolbar->removeAction(getAction("filter"));

    _menu->removeAction(getAction("previous"));
    _menu->removeAction(getAction("openInExplorer"));
    _menu->removeAction(getAction("open"));
    _menu->removeAction(getAction("rename"));
    _menu->removeAction(getAction("filter"));
}

void MainWindow::showTagList() {

    hideWidget();

    // Adding TagList specific actions
    _menu->addAction(getAction("rename"));
    _menu->addAction(getAction("filter"));

    _toolbar->addAction(getAction("rename"));
    _toolbar->addAction(getAction("filter"));


    setWindowTitle("Tagulous");
    // Showing tags
    _tagListWidget->connectActions(_actions);
    _stackedWidget->setCurrentWidget(_tagListWidget);
}

void MainWindow::showFileList(QModelIndexList *indexes) {

    hideWidget();

    // Adding FileList specific actions
    _menu->addAction(getAction("previous"));
    _menu->addAction(getAction("open"));
    _menu->addAction(getAction("openInExplorer"));

    _toolbar->addAction(getAction("previous"));
    _toolbar->addAction(getAction("open"));
    _toolbar->addAction(getAction("openInExplorer"));


    // Creating a model with all the tagged file that we want to show
    QString windowTitle;
    QList<Tag *> *lst = new QList<Tag *>;
    for (QModelIndex index : *indexes) {
        lst->append(_tagList->at(index.row()));
        if (windowTitle == "") {
            windowTitle += _tagList->at(index.row())->getName();
        } else {
            windowTitle += " - " + _tagList->at(index.row())->getName();
        }
    }
    setWindowTitle(windowTitle);
    delete indexes;

    FileListModel *m = new FileListModel(lst);
    _fileListWidget->setModel(m);

    // Showing tagged files
    _fileListWidget->connectActions(_actions);
    _stackedWidget->setCurrentWidget(_fileListWidget);
}

QAction *MainWindow::getAction(QString key) {
    return _actions->value(key);
}

MainWindow::~MainWindow() {
    // When quitting the app we save the data to the disk
    savePersistance(_tagList);

    // Deleting what was allocated
    QMapIterator<QString, QAction *> i(*_actions);
    while (i.hasNext()) {
        i.next();
        delete i.value();
    }
    delete _actions;
    delete _toolbar;
    delete _menu;
    delete _menuBar;

    delete _tagListWidget;
    delete _fileListWidget;
    delete _stackedWidget;

    delete _tagListModel;
    delete _tagList;

}
