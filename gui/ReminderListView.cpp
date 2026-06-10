#include "ReminderListView.h"

#include <QHBoxLayout>
#include <QLabel>

ReminderListView::ReminderListView(QWidget *parent) : QWidget(parent) {
    listWidget = new QListWidget(this);
    addButton = new QPushButton("Add", this);

    listWidget->setResizeMode(QListView::Adjust);
    listWidget->setSpacing(10);

    QWidget *buttonWidget = new QWidget(this);
    QHBoxLayout *hlayout = new QHBoxLayout();
    hlayout->addWidget(addButton);
    buttonWidget->setLayout(hlayout);    

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(buttonWidget);
    layout->addWidget(listWidget);

    setLayout(layout);
    connect(listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SIGNAL(reminderSelected(QListWidgetItem*)));
    connect(addButton, &QPushButton::clicked, this, &ReminderListView::addClicked);
}

void ReminderListView::displayReminderList(const ReminderList& l) {
    list = new ReminderList(l);
    clear();

    for(auto it=list->begin(); it!=list->end(); ++it) {
        QListWidgetItem *item = new QListWidgetItem();
        QVariant id((*it)->getId());
        item->setData(Qt::UserRole, id);

        QWidget *widget = new QWidget(this);
        QLabel *titleLabel = new QLabel((*it)->getTitle(), widget);
        QLabel *descrLabel = new QLabel((*it)->getDescr(), widget);
       
        QHBoxLayout *wlayout = new QHBoxLayout();
        wlayout->addWidget(titleLabel);
        wlayout->addWidget(descrLabel);
        wlayout->addStretch();
        wlayout->setSizeConstraint(QLayout::SetFixedSize);
        widget->setLayout(wlayout);
        item->setSizeHint(widget->sizeHint());       
    
        listWidget->addItem(item);
        listWidget->setItemWidget(item, widget);
    }
}

AbstractReminder& ReminderListView::getReminder(const unsigned int id) const {
    return list->get(id);
}

ReminderList& ReminderListView::searchReminders(const QString text) const {
    return list->search(text);
}

ReminderList& ReminderListView::getRemindersByDate(const QDate& date) const {
    return list->getByDate(date);
}

unsigned int ReminderListView::getCounter() const {
    return list->getCounter();
}

void ReminderListView::clear() {
    listWidget->clear();
}

void ReminderListView::insertReminder(AbstractReminder& reminder) {
    list->add(reminder);
    displayReminderList(*list);
}

void ReminderListView::removeReminder(unsigned int id) {
    list->remove(id);
    displayReminderList(*list);
}
