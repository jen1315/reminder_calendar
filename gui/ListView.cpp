#include "ListView.h"
#include "ListWidget.h"

#include <QHBoxLayout>
#include <QLabel>

ListView::ListView(QWidget *parent) : QWidget(parent) {
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
    connect(addButton, &QPushButton::clicked, this, &ListView::addClicked);
}

void ListView::displayReminderList(const ReminderList& l) {
    list = new ReminderList(l);
    clear();

    for(auto it=list->begin(); it!=list->end(); ++it) {
        QListWidgetItem *item = new QListWidgetItem();
        QVariant id((*it)->getId());
        item->setData(Qt::UserRole, id);

        QWidget *widget = new QWidget(this);
        QLabel *titleLabel = new QLabel((*it)->getTitle(), widget);
        
        ListWidget *visitor = new ListWidget();
        (*it)->accept(visitor);

        QVBoxLayout *wlayout = new QVBoxLayout();
        wlayout->addWidget(titleLabel);
        wlayout->addWidget(visitor->getWidget());
        wlayout->setSizeConstraint(QLayout::SetFixedSize);
        widget->setLayout(wlayout);
        item->setSizeHint(widget->sizeHint());

        listWidget->addItem(item);
        listWidget->setItemWidget(item, widget);
    }
}

AbstractReminder& ListView::getReminder(const unsigned int id) const {
    return list->get(id);
}

ReminderList& ListView::searchReminders(const QString text) const {
    return list->search(text);
}

ReminderList& ListView::getRemindersByDate(const QDate& date) const {
    return list->getByDate(date);
}

ReminderList& ListView::getReminderList() const {
    return *list;
}

unsigned int ListView::getSize() const {
    return list->getSize();
}

void ListView::clear() {
    listWidget->clear();
}

void ListView::insertReminder(AbstractReminder& reminder) {
    list->add(reminder);
    displayReminderList(*list);
}

void ListView::removeReminder(unsigned int id) {
    list->remove(id);
    displayReminderList(*list);
}
