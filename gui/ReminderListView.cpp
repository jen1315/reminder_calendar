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

void ReminderListView::displayReminderList(QMap<int, AbstractReminder*>& l) {
    list = new QMap<int, AbstractReminder*>(l);
    clear();
    for(auto it=l.begin(); it!=l.end(); ++it) {
        QListWidgetItem *item = new QListWidgetItem();
        QVariant reminder((*it)->getId());
        item->setData(Qt::UserRole, reminder);

        QWidget *widget = new QWidget(this);
        QLabel *titleLabel = new QLabel((*it)->getTitle(), widget);
       
        QHBoxLayout *wlayout = new QHBoxLayout();
        wlayout->addWidget(titleLabel);
        wlayout->addWidget(yearLabel);
        wlayout->addStretch();
        wlayout->setSizeConstraint(QLayout::SetFixedSize);
        widget->setLayout(wlayout);
        item->setSizeHint(widget->sizeHint());       
    
        listWidget->addItem(item);
        listWidget->setItemWidget(item, widget);
    }
}

AbstractReminder& ReminderListView::getReminder(int id) {
    return *((*list)[id]);
}

void ReminderListView::setReminder(AbstractReminder& reminder) {
    int id = reminder.getId();
    (*list)[id] = &reminder;
    displayReminder(*list);
}

QMap<int, AbstractReminder*>& ReminderListView::getReminderList() const {
    return *list;
}

void ReminderList::clear() {
    listWidget->clear();
}

void ReminderListView::addReminder(AbstractReminder& reminder) {
    int id = list->size();
    reminder.setId(id);
    (*list)[id] = &reminder;
    displayReminder(*list);
}

void ReminderListView::removeReminder() {
}
