#include "ReminderView.h"

#include "Utilities.h"

ReminderView::ReminderView(QWidget *parent) : QWidget(parent) {
    titleLabel = new QLabel(this);
    descrLabel = new QLabel(this);
    visitLayout = new QVBoxLayout();
    layout = new QVBoxLayout();
    editButton = new QPushButton("Edit", this);
    deleteButton = new QPushButton("Delete", this);
    
    titleLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    descrLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    QHBoxLayout *hlayout = new QHBoxLayout();  
    hlayout->addWidget(editButton);
    hlayout->addWidget(deleteButton);

    QVBoxLayout *vlayout = new QVBoxLayout();
    vlayout->addLayout(hlayout);
    vlayout->addWidget(titleLabel);
    vlayout->addWidget(descrLabel);
    vlayout->addLayout(visitLayout);

    layout->addLayout(vlayout);

    connect(editButton, &QPushButton::clicked, this, &ReminderView::toEdit);
    connect(deleteButton, &QPushButton::clicked, this, &ReminderView::toDelete);

    setLayout(layout);
}

void ReminderView::displayReminder(AbstractReminder& m) {
    Utilities::clearLayout(visitLayout);
    reminder = &m;
    titleLabel->setText("Title: " + m.getTitle());
    descrLabel->setText(m.getDescr());
    
    ReminderWidget *visitor = new ReminderWidget();
    m.accept(visitor);
    visitLayout->addWidget(visitor->getWidget());
}

AbstractReminder& ReminderView::getReminder() const {
    return *reminder;
}

void ReminderView::toDelete() {
    emit deleted(reminder->getId());
}
