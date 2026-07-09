#include "ViewManager.h"

#include <QDebug>
#include <QToolBar>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QStatusBar>

ViewManager::ViewManager(QWidget *parent) : QMainWindow(parent) {
    json = nullptr;
    stackWidget = new QStackedWidget(this);
    searchBar = new QLineEdit(this);
    searchButton = new QPushButton("Search", this);
    homeButton = new QPushButton("All reminders", this);
    importButton = new QPushButton("Load", this);
    newButton = new QPushButton("New file", this);
    
    nextView = new ListView(this);
    reminderView = new ReminderView(this);
    searchView = new ListView(this);
    editView = new EditView(this);
    addView = new AddView(this);
    calendarView = new CalendarView(this);

    stackWidget->addWidget(nextView);
    stackWidget->addWidget(reminderView);
    stackWidget->addWidget(searchView);
    stackWidget->addWidget(editView);
    stackWidget->addWidget(addView);

    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(calendarView);
    layout->addWidget(stackWidget);
    QWidget *widget = new QWidget(this);
    widget->setLayout(layout);

    connect(newButton, &QPushButton::clicked, this, &ViewManager::newFile);
    connect(importButton, &QPushButton::clicked, this, &ViewManager::loadFile);
    connect(homeButton, &QPushButton::clicked, this, &ViewManager::switchHome);
    connect(nextView, SIGNAL(reminderSelected(QListWidgetItem*)), this, SLOT(viewReminder(QListWidgetItem*)));
    connect(searchButton, &QPushButton::clicked, this, &ViewManager::viewSearch);
    connect(searchView, SIGNAL(reminderSelected(QListWidgetItem*)), this, SLOT(viewReminder(QListWidgetItem*)));
    connect(reminderView, &ReminderView::toEdit, this, &ViewManager::viewEdit);
    connect(editView, SIGNAL(submitted(AbstractReminder*)), this, SLOT(editReminder(AbstractReminder*)));
    connect(nextView, &ListView::addClicked, this, &ViewManager::viewAdd);
    connect(addView, SIGNAL(submitted(AbstractReminder*)), this, SLOT(addReminder(AbstractReminder*)));
    connect(reminderView, SIGNAL(deleted(unsigned int)), this, SLOT(deleteReminder(unsigned int)));
    connect(calendarView, SIGNAL(dateSelected(QDate)), this, SLOT(viewSearchSelected(QDate)));

    QToolBar *toolbar = new QToolBar(this);
    toolbar->addWidget(newButton);
    toolbar->addWidget(importButton);
    toolbar->insertSeparator(toolbar->addWidget(searchBar));
    toolbar->addWidget(searchButton);
    toolbar->insertSeparator(toolbar->addWidget(homeButton));
    
    addToolBar(Qt::TopToolBarArea, toolbar);
    setCentralWidget(widget);
    statusBar()->showMessage(tr("No file loaded"));
}

void ViewManager::loadReminders(QString fileName) {
    if(fileName!="") {
        json = new JsonFile(fileName);
        statusBar()->showMessage(tr(fileName.toStdString().c_str()));
    }
}

void ViewManager::newFile() {
    QString fileName = QFileDialog::getSaveFileName(this, 
        tr("Create file"), "/home", tr("Json file (*.json)"));
    loadReminders(fileName);
}

void ViewManager::loadFile() {
    QString fileName = QFileDialog::getOpenFileName(this, 
        tr("Load file"), "/home", tr("Json file (*.json)"));
    loadReminders(fileName);
    if(json) {
        nextView->displayReminderList(json->getList());
        calendarView->highlightReminders(nextView->getReminderList());
    }
}

void ViewManager::viewReminder(QListWidgetItem* item) {
    int id = (item->data(Qt::UserRole)).toInt();
    reminderView->displayReminder(nextView->getReminder(id));
    stackWidget->setCurrentIndex(1);
}

void ViewManager::viewSearch() {
    searchView->clear();
    QString item = searchBar->text();
    if (!item.isEmpty()) {
        searchView->displayReminderList(nextView->searchReminders(item));
        searchBar->clear();
        stackWidget->setCurrentIndex(2);
    }
}

void ViewManager::viewSearchSelected(QDate date) {
    searchView->clear();
    searchView->displayReminderList(nextView->getRemindersByDate(date));
    stackWidget->setCurrentIndex(2);
}

void ViewManager::viewEdit() {
    editView->setReminder(reminderView->getReminder());
    stackWidget->setCurrentIndex(3);
}

void ViewManager::viewAdd() {
    stackWidget->setCurrentIndex(4);
}

void ViewManager::switchHome() {
    stackWidget->setCurrentIndex(0);
}

void ViewManager::editReminder(AbstractReminder* reminder) {
    nextView->insertReminder(*reminder);
    json->save(*reminder, false);
    reminderView->displayReminder(*reminder);
    calendarView->highlightReminders(nextView->getReminderList());
    stackWidget->setCurrentIndex(1);
}

void ViewManager::addReminder(AbstractReminder* reminder) {
    if(!json)
        newFile();
    if(json) {
        reminder->setId(nextView->getSize());
        nextView->insertReminder(*reminder);
        json->save(*reminder, true);
        addView->clear();
        reminderView->displayReminder(*reminder);
        calendarView->highlight(*reminder);
        stackWidget->setCurrentIndex(1);
    }
}

void ViewManager::deleteReminder(unsigned int id) {
    nextView->removeReminder(id);
    json->erase(id);
    calendarView->highlightReminders(nextView->getReminderList());
    switchHome();
}