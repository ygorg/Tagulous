#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    tagList = new QList<Tag *>();
    tagListModel = new TagListModel(tagList);

    Tag *tag = new Tag("Tag1");
    tagList->append(tag);
    tag = new Tag("Tag2");
    tagList->append(tag);
    tag = new Tag("Tag3");
    tagList->append(tag);


    listView = new QListView();
    listView->setModel(tagListModel);
    listView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    listView->setDragEnabled(true);
    listView->setAcceptDrops(true);
    listView->setDropIndicatorShown(true);
    listView->setAttribute(Qt::WA_MacShowFocusRect, false);

    QPushButton *btn = new QPushButton(tr("Add tag"), this);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(listView);
    layout->addWidget(btn);

    setCentralWidget(new QWidget);
    centralWidget()->setLayout(layout);

    connect(btn, SIGNAL(clicked(bool)),
            tagListModel, SLOT(requestedAddTag()));
}