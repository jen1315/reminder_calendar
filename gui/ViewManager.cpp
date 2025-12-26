#include "ViewManager.h"
#include <QDebug>
#include <QToolBar>
#include "./model/Utilities.h"

ViewManager::ViewManager(QWidget *parent) : QMainWindow(parent) {
    stackWidget = new QStackedWidget(this);
    homeButton = new QPushButton("Home", this);
    searchBar = new QLineEdit(this);
    searchButton = new QPushButton("Search", this);

    libraryView = new LibraryView(this);
    mediaView = new MediaView(this);
    searchView = new LibraryView(this);
    editView = new EditView(this);
    addView = new AddView(this);

    stackWidget->addWidget(libraryView);
    stackWidget->addWidget(mediaView);
    stackWidget->addWidget(searchView);
    stackWidget->addWidget(editView);
    stackWidget->addWidget(addView);

    connect(homeButton, &QPushButton::clicked, this, &ViewManager::switchHome);
    connect(libraryView, SIGNAL(mediaSelected(QListWidgetItem*)), this, SLOT(viewMedia(QListWidgetItem*)));
    connect(searchButton, &QPushButton::clicked, this, &ViewManager::viewSearch);
    connect(searchView, SIGNAL(mediaSelected(QListWidgetItem*)), this, SLOT(viewMedia(QListWidgetItem*)));
    connect(mediaView, &MediaView::toEdit, this, &ViewManager::viewEdit);
    connect(editView, SIGNAL(submitted(AbstractReminder*)), this, SLOT(submitMedia(AbstractReminder*)));
    connect(libraryView, &LibraryView::addClicked, this, &ViewManager::viewAdd);
    connect(addView, SIGNAL(submitted(AbstractReminder*)), this, SLOT(addMedia(AbstractReminder*)));

    QToolBar *toolbar = new QToolBar(this);
    toolbar->addWidget(homeButton);
    toolbar->addWidget(searchBar);
    toolbar->addWidget(searchButton);
    
    addToolBar(Qt::TopToolBarArea, toolbar);
    setCentralWidget(stackWidget);
}

void ViewManager::setMedia(QMap<int, AbstractReminder*>& lib) {
    libraryView->displayReminder(lib);
}

void ViewManager::viewMedia(QListWidgetItem* item) {
    int id = (item->data(Qt::UserRole)).toInt();
    mediaView->displayReminder(libraryView->getReminder(id));
    stackWidget->setCurrentIndex(1);
}

void ViewManager::viewSearch() {
    searchView->clear();
    QString item = searchBar->text();
    if (!item.isEmpty()) {
        searchView->displayReminder(Util::search(libraryView->getLibrary(), item));
        searchBar->clear();
        stackWidget->setCurrentIndex(2);
    }
}

void ViewManager::viewEdit() {
    editView->setMedia(mediaView->getReminder());
    stackWidget->setCurrentIndex(3);
}

void ViewManager::viewAdd() {
    stackWidget->setCurrentIndex(4);
}

void ViewManager::switchHome() {
    stackWidget->setCurrentIndex(0);
}

void ViewManager::submitMedia(AbstractReminder* reminder) {
    libraryView->setMedia(*reminder);
    mediaView->displayReminder(*reminder);
    stackWidget->setCurrentIndex(1);
}

void ViewManager::addMedia(AbstractReminder* reminder) {
    libraryView->addMedia(*reminder);
    mediaView->displayReminder(*reminder);
    stackWidget->setCurrentIndex(1);
}
