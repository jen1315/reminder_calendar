#include "ReminderWidget.h"

#include <QLabel>
#include <QVBoxLayout>
#include <QDateTimeEdit>
#include <QCheckBox>
#include <QFormLayout>
#include "../model/Event.h"
#include "../model/Deadline.h"
#include "../model/Memo.h"

ReminderWidget::ReminderWidget(QWidget *parent) : QWidget(parent) {}

QWidget* ReminderWidget::getWidget() {
    return widget;
}

void ReminderWidget::visit(const Event *event) {
    widget = new QWidget(this);
    QLabel *startLabel = new QLabel("Starts: "+ event->getStartDate().toString("d ddd MMMM yyyy"), widget);
    QLabel *endLabel = new QLabel("Ends: "+ event->getEndDate().toString("d ddd MMMM yyyy"), widget);
    QLabel *startTimeLabel = new QLabel(widget);
    QLabel *endTimeLabel = new QLabel(widget);
    if(event->getHasTime()) {
        startTimeLabel->setText("at: "+ event->getStartDate().toString("hh:mm:ss"));
        endTimeLabel->setText("at: "+ event->getEndDate().toString("hh:mm:ss"));
    }

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(startLabel);
    layout->addWidget(startTimeLabel);
    layout->addWidget(endLabel);
    layout->addWidget(endTimeLabel);
    widget->setLayout(layout);
}

void ReminderWidget::visit(const Deadline *deadline) {
    widget = new QWidget(this);
    QLabel *dateLabel = new QLabel("Date: " + deadline->getDate().toString("d ddd MMMM yyyy"), widget);
    QLabel *timeLabel = new QLabel(widget);
    QString isDone = deadline->getIsDone()?"Yes":"No";
    QLabel *doneLabel = new QLabel("Is it done? " + isDone, widget);
    if(deadline->getHasTime())
        timeLabel->setText("at: "+ deadline->getDate().toString("hh:mm:ss"));

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(dateLabel);
    layout->addWidget(timeLabel);
    layout->addWidget(doneLabel);
    widget->setLayout(layout);
}

void ReminderWidget::visit(const Memo *memo) {
    widget = new QWidget(this);
    QString isDone = memo->getIsDone()?"Yes":"No";
    QLabel *doneLabel = new QLabel("Is it done? " + isDone, widget);
    
    QVBoxLayout *layout = new QVBoxLayout(widget);
    layout->addWidget(doneLabel);
    widget->setLayout(layout);
}