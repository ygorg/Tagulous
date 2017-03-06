#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    tagList = new QList<Tag *>();
    tagListModel = new TagListModel(tagList, 0);

    Tag *tag = new Tag("Tag1");
    tag->setBulletColor(QColor(252, 61, 57));
    tagList->append(tag);

    tag = new Tag("Tag2");
    tag->setBulletColor(QColor(104, 216, 69));
    tagList->append(tag);

    tag = new Tag("Tag3");
    tag->setBulletColor(QColor(42, 174, 245));
    tagList->append(tag);


    listView = new QListView();
    listView->setModel(tagListModel);
    listView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    listView->setDragEnabled(true);
    listView->setAcceptDrops(true);
    listView->setDropIndicatorShown(true);
    listView->setAttribute(Qt::WA_MacShowFocusRect, false);

    QPushButton *btn = new QPushButton(tr("Nouveau tag"), this);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(listView);
    layout->addWidget(btn);

    setCentralWidget(new QWidget);
    centralWidget()->setLayout(layout);

    connect(btn, SIGNAL(clicked(bool)),
            tagListModel, SLOT(requestedAddTag()));
}
