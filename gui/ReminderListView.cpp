#include "ReminderListView.h"

#include <QHBoxLayout>
#include <QLabel>

ReminderListView::ReminderListView(QWidget *parent) : QWidget(parent) {
    listWidget = new QListWidget(this);
    addButton = new QPushButton("Add", this);

    listWidget->setResizeMode(QListView::Adjust);
    listWidget->setSpacing(10);

    QWidget *buttonWidget = new QWidget(this);
    QVBoxLayout *vlayout = new QVBoxLayout();
    vlayout->addWidget(addButton);
    buttonWidget->setLayout(vlayout);    

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(buttonWidget);
    layout->addWidget(listWidget);

    setLayout(layout);
    connect(listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SIGNAL(reminderSelected(QListWidgetItem*)));
    connect(addButton, &QPushButton::clicked, this, &ReminderListView::addClicked);
}

void ReminderListView::displayReminderList(ReminderList& l) {
    list = new ReminderList(l);
    clear();
/*
    for(auto it : l.getReminders()) {
        QListWidgetItem *item = new QListWidgetItem();
        QVariant reminder((*it)->getId());
        item->setData(Qt::UserRole, reminder);

        QWidget *widget = new QWidget(this);
        QLabel *titleLabel = new QLabel((*it)->getTitle(), widget);
       
        QHBoxLayout *wlayout = new QHBoxLayout();
        wlayout->addWidget(titleLabel);
        wlayout->addWidget(descrLabel);
        wlayout->addStretch();
        wlayout->setSizeConstraint(QLayout::SetFixedSize);
        widget->setLayout(wlayout);
        item->setSizeHint(widget->sizeHint());       
    
        listWidget->addItem(item);
        listWidget->setItemWidget(item, widget);
    }*/
}

AbstractReminder& ReminderListView::getReminder(const unsigned int id) const {
    return list->get(id);
}

void ReminderListView::setReminder(AbstractReminder& reminder) {
    int id = reminder.getId();
    list->add(reminder);
    displayReminderList(*list);
}

ReminderList& ReminderListView::getReminderList() const {
    return *list;
}

void ReminderListView::clear() {
    listWidget->clear();
}

void ReminderListView::addReminder(AbstractReminder& reminder) {
    reminder.setId(list->getNumElem());
    ReminderListView::setReminder(reminder);
}

void ReminderListView::removeReminder() {
}
