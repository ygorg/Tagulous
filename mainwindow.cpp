#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{

    qDebug() << "BUG QSortFilterProxyModel::rowCount() is bugged so subclassing QAbstractProxyModel is needed...\n"
                "FIX QFileDialog doesn't allow files adn dirs to be selected at the same time...";

    createActions();

    _tagList = new TagList;

    QFile file(_path + "/" + _fileName);
    QString data;
    if (file.open(QIODevice::ReadOnly))
    {
        QXmlStreamReader *reader = new QXmlStreamReader(&file);
        _tagList->fromXML(reader);
        file.close();
    } else {
        _tagList->init();
        qDebug() << "Unable to load the data.";
    }

    _tagListModel = new TagListModelDrop(_tagList);

    _tagListWidget = new TagListWidget(_tagListModel, _actions);    
    connect(_tagListWidget, SIGNAL(toolBarAction(QString)),
            this, SLOT(addToolBarAction(QString)));

    connect(_tagListWidget, SIGNAL(viewFileList(int)),
            this, SLOT(showFileList(int)));

    _fileListWidget = new FileListWidget(_actions);
    connect(_fileListWidget, SIGNAL(toolBarAction(QString)),
            this, SLOT(addToolBarAction(QString)));

    connect(_fileListWidget, SIGNAL(viewTagList()),
            this, SLOT(showTagList()));

    _stackedWidget->addWidget(_tagListWidget);
    _stackedWidget->addWidget(_fileListWidget);
    setCentralWidget(_stackedWidget);
    showTagList();

}

void MainWindow::hideWidget() {


    QMapIterator<QString, QAction *> i(*_actions);
    while (i.hasNext()) {
        i.next();
        disconnect(i.value(), SIGNAL(triggered()), 0, 0);
        _toolbar->removeAction(i.value());
        //_menu->removeAction(i.value());
    }

    _menu->removeAction(getAction("previous"));
    _menu->removeAction(getAction("openInExplorer"));
    _menu->removeAction(getAction("open"));
    _menu->removeAction(getAction("rename"));
    _menu->removeAction(getAction("filter"));

}

void MainWindow::showTagList() {

    hideWidget();

    _menu->addAction(getAction("rename"));
    _menu->addAction(getAction("filter"));

    _tagListWidget->connectActions();
    _stackedWidget->setCurrentWidget(_tagListWidget);
}

void MainWindow::showFileList(int row) {

    hideWidget();

    _menu->addAction(getAction("previous"));
    _menu->addAction(getAction("openInExplorer"));
    _menu->addAction(getAction("open"));

    FileListModel *m = new FileListModel(_tagList->at(row));
    _fileListWidget->setModel(m);

    _fileListWidget->connectActions();
    _stackedWidget->setCurrentWidget(_fileListWidget);
}

QAction *MainWindow::getAction(QString key) {
    return _actions->value(key);
}

void MainWindow::createActions() {
    /* Some icones might be here :
     * /System/Library/CoreServices/SystemAppearance.bundle/Contents/Resources
     */
    // General Actions
    QAction *addAction = new QAction(QIcon::fromTheme("list-add"), tr("Add"), this);
    addAction->setShortcut(QKeySequence::New);
    _actions->insert("add", addAction);

    QAction *copyAction = new QAction(tr("Copy"), this);
    copyAction->setShortcut(QKeySequence::Copy);
    _actions->insert("copy", copyAction);


    QAction *pasteAction = new QAction(tr("Paste"), this);
    pasteAction->setShortcut(QKeySequence::Paste);
    _actions->insert("paste", pasteAction);


    QAction *removeAction = new QAction(tr("Remove"), this);
#ifdef Q_OS_MAC
    removeAction->setShortcut(QKeySequence(Qt::Key_Backspace));
#else
    removeAction->setShortcut(QKeySequence::Delete);
#endif /* Q_OS_MAC */
    _actions->insert("remove", removeAction);

    QAction *findAction = new QAction(tr("Search"), this);
    findAction->setShortcut(QKeySequence::Find);
    _actions->insert("find", findAction);


    // TagListWindget specific actions
    QAction *renameAction = new QAction(tr("Rename"), this);
    _actions->insert("rename", renameAction);

    QAction *filterAction = new QAction(tr("Filter"), this);
    _actions->insert("filter", filterAction);

    // FileListWidget specific actions
    QAction *previousAction = new QAction(tr("Back"), this);
    previousAction->setShortcut(QKeySequence::Back);
    _actions->insert("previous", previousAction);

    QAction *openInExplorerAction = new QAction(tr("Open in Finder"), this);
    _actions->insert("openInExplorer", openInExplorerAction);

    QAction *openAction = new QAction(tr("Open"), this);
    openAction->setShortcut(QKeySequence::Open);
    _actions->insert("open", openAction);


    setUnifiedTitleAndToolBarOnMac(true);
    _toolbar->setMovable(false);
    _toolbar->setFloatable(false);

    _menuBar->addMenu(_menu);
    this->addToolBar(_toolbar);

    _menu->addAction(addAction);
    _menu->addAction(copyAction);
    _menu->addAction(pasteAction);
    _menu->addAction(removeAction);
    _menu->addAction(findAction);
}


void MainWindow::addToolBarAction(QString value) {
    _toolbar->addAction(_actions->value(value));
}

MainWindow::~MainWindow() {
    QDir d;
    d.mkpath(_path);

    QFile file(_path + "/" + _fileName);
    if (file.open(QIODevice::WriteOnly))
    {
        QXmlStreamWriter *writer = new QXmlStreamWriter(&file);
        _tagList->toXML(writer);
        file.close();
        delete writer;
    } else {
        qDebug() << "Unable to save the data.";
    }

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
