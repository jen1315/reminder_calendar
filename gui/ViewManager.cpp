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
    connect(editView, SIGNAL(submitted(AbstractMedia*)), this, SLOT(submitMedia(AbstractMedia*)));
    connect(libraryView, &LibraryView::addClicked, this, &ViewManager::viewAdd);
    connect(addView, SIGNAL(submitted(AbstractMedia*)), this, SLOT(addMedia(AbstractMedia*)));

    QToolBar *toolbar = new QToolBar(this);
    toolbar->addWidget(homeButton);
    toolbar->addWidget(searchBar);
    toolbar->addWidget(searchButton);
    
    addToolBar(Qt::TopToolBarArea, toolbar);
    setCentralWidget(stackWidget);
}

void ViewManager::setMedia(QMap<int, AbstractMedia*>& lib) {
    libraryView->displayMedia(lib);
}

void ViewManager::viewMedia(QListWidgetItem* item) {
    int id = (item->data(Qt::UserRole)).toInt();
    mediaView->displayMedia(libraryView->getMedia(id));
    stackWidget->setCurrentIndex(1);
}

void ViewManager::viewSearch() {
    searchView->clear();
    QString item = searchBar->text();
    if (!item.isEmpty()) {
        searchView->displayMedia(Util::search(libraryView->getLibrary(), item));
        searchBar->clear();
        stackWidget->setCurrentIndex(2);
    }
}

void ViewManager::viewEdit() {
    editView->setMedia(mediaView->getMedia());
    stackWidget->setCurrentIndex(3);
}

void ViewManager::viewAdd() {
    stackWidget->setCurrentIndex(4);
}

void ViewManager::switchHome() {
    stackWidget->setCurrentIndex(0);
}

void ViewManager::submitMedia(AbstractMedia* media) {
    libraryView->setMedia(*media);
    mediaView->displayMedia(*media);
    stackWidget->setCurrentIndex(1);
}

void ViewManager::addMedia(AbstractMedia* media) {
    libraryView->addMedia(*media);
    mediaView->displayMedia(*media);
    stackWidget->setCurrentIndex(1);
}
