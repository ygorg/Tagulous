#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{

    qDebug() << "TODO Add support for the search field\n"
             << "TODO connect viewFileList and implement\n"
             << "TODO Add drag'n'drop support in FileListModel\n"
             << "TODO Implement FileListWidget\n"
             << "TODO Adding files to a Tag shall SIGNAL some dataChanged\n";

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

    showTagList();

}

void MainWindow::showTagList() {
    setCentralWidget(_tagListWidget);

    connect(_tagListWidget, SIGNAL(menuAction(QString)),
            this, SLOT(addMenuAction(QString)));
    connect(_tagListWidget, SIGNAL(toolBarAction(QString)),
            this, SLOT(addToolBarAction(QString)));

    _tagListWidget->connectActions();
}

/*void MainWindow::showFileList() {
    _fileListWidget = new _fileListWidget();
    setCentralWidget(_fileListWidget);

    connect(_tagListWidget, SIGNAL(menuAction(QString)),
            this, SLOT(addMenuAction(QString)));
    connect(_tagListWidget, SIGNAL(toolBarAction(QString)),
            this, SLOT(addToolBarAction(QString)));
}*/

QAction *MainWindow::getAction(QString key) {
    return _actions->value(key);
}

void MainWindow::createActions() {

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


    QAction *removeAction = new QAction(tr("Delete"), this);
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

    QAction *openInExplorerAction = new QAction(tr("Open in explorer"), this);
    _actions->insert("openInExplorer", openInExplorerAction);

    QAction *openAction = new QAction(tr("Open"), this);
    openAction->setShortcut(QKeySequence::Open);
    _actions->insert("open", openAction);

    /*QMapIterator<QString, QAction *> i(*_actions);
    while (i.hasNext()) {
        i.next();
        _menu->addAction(i.value());
        _toolbar->addAction(i.value());
    }*/

    setUnifiedTitleAndToolBarOnMac(true);
    _toolbar->setMovable(false);
    _toolbar->setFloatable(false);

    _menuBar->addMenu(_menu);
    this->addToolBar(_toolbar);

}

/* Some icones might be here :
 * /System/Library/CoreServices/SystemAppearance.bundle/Contents/Resources
 */

/*void MainWindow::createFileListActions() {
    //connect add, remove, copy, paste
    //go back, open in finder, open

    connect(addAction, SIGNAL(triggered(bool)),
            tagListModel, SLOT(requestedAddTag()));
    connect(copyAction, SIGNAL(triggered(bool)),
            this, SLOT(copyElement()));
    connect(pasteAction, SIGNAL(triggered(bool)),
            this, SLOT(pasteElement()));
    connect(deleteAction, SIGNAL(triggered(bool)),
            this, SLOT(deleteElement()));
}*/

MainWindow::~MainWindow() {

    QDir d;
    d.mkpath(_path);

    QFile file(_path + "/" + _fileName);
    if (file.open(QIODevice::WriteOnly))
    {
        QXmlStreamWriter *writer = new QXmlStreamWriter(&file);
        _tagList->toXML(writer);
        file.close();
    } else {
        qDebug() << "Unable to save the data.";
    }
}

void MainWindow::addToolBarAction(QString value) {
    _toolbar->addAction(_actions->value(value));
}

void MainWindow::addMenuAction(QString value) {
    _menu->addAction(_actions->value(value));
}
